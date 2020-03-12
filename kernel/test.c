// Build with: gcc -pthread test.c
//
// This demonstrates an issue where AVX state becomes corrupted when a
// signal is delivered where the signal stack pages aren't faulted in.
//
// There appear to be three necessary ingredients, which are marked
// with "!!!" below:
//
// 1. A thread doing AVX operations using YMM registers.
//
// 2. A signal where the kernel must fault in stack pages to write the
//    signal context.
//
// 3. Context switches. Having a single task isn't sufficient.

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/prctl.h>
#include <sys/wait.h>

static int sigs;

static stack_t altstack;
static pthread_t tid;

static void die(const char* msg, int err) {
  if (err != 0) {
    fprintf(stderr, "%s: %s\n", msg, strerror(err));
  } else {
    fprintf(stderr, "%s\n", msg);
  }
  exit(EXIT_FAILURE);
}

void handler(int sig __attribute__((unused)),
             siginfo_t* info __attribute__((unused)),
             void* context __attribute__((unused))) {
  sigs++;
}

void* sender(void *arg) {
  int err;

  for (;;) {
    usleep(100);
    err = pthread_kill(tid, SIGWINCH);
    if (err != 0)
      die("pthread_kill", err);
  }
  return NULL;
}

void dump(const char *label, unsigned char *data) {
  printf("%s =", label);
  for (int i = 0; i < 32; i++)
    printf(" %02x", data[i]);
  printf("\n");
}

void doAVX(void) {
  unsigned char input[32];
  unsigned char output[32];

  // Set input to a known pattern.
  for (int i = 0; i < sizeof input; i++)
    input[i] = i;
  // Mix our PID in so we detect cross-process leakage, though this
  // doesn't appear to be what's happening.
  pid_t pid = getpid();
  memcpy(input, &pid, sizeof pid);

  while (1) {
    for (int i = 0; i < 1000; i++) {
      // !!! Do some computation we can check using YMM registers.
      asm volatile(
        "vmovdqu %1, %%ymm0;"
        "vmovdqa %%ymm0, %%ymm1;"
        "vmovdqa %%ymm1, %%ymm2;"
        "vmovdqa %%ymm2, %%ymm3;"
        "vmovdqu %%ymm3, %0;"
        : "=m" (output)
        : "m" (input)
        : "memory", "ymm0", "ymm1", "ymm2", "ymm3");
      // Check that input == output.
      if (memcmp(input, output, sizeof input) != 0) {
        dump("input ", input);
        dump("output", output);
        die("mismatch", 0);
      }
    }

    // !!! Release the pages of the signal stack. This is necessary
    // because the error happens when copy_fpstate_to_sigframe enters
    // the failure path that handles faulting in the stack pages.
    // (mmap with MMAP_FIXED also works.)
    //
    // (We do this here to ensure it doesn't race with the signal
    // itself.)
    if (madvise(altstack.ss_sp, altstack.ss_size, MADV_DONTNEED) != 0)
      die("madvise", errno);
  }
}

void doTest() {
  // Create an alternate signal stack so we can release its pages.
  void *altSigstack = mmap(NULL, SIGSTKSZ, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
  if (altSigstack == MAP_FAILED)
    die("mmap failed", errno);
  altstack.ss_sp = altSigstack;
  altstack.ss_size = SIGSTKSZ;
  if (sigaltstack(&altstack, NULL) < 0)
    die("sigaltstack", errno);

  // Install SIGWINCH handler.
  struct sigaction sa = {
    .sa_sigaction = handler,
    .sa_flags = SA_ONSTACK | SA_RESTART,
  };
  sigfillset(&sa.sa_mask);
  if (sigaction(SIGWINCH, &sa, NULL) < 0)
    die("sigaction", errno);

  // Start thread to send SIGWINCH.
  int err;
  pthread_t ctid;
  tid = pthread_self();
  if ((err = pthread_create(&ctid, NULL, sender, NULL)) != 0)
    die("pthread_create sender", err);

  // Run test.
  doAVX();
}

void *exiter(void *arg) {
  sleep(60);
  exit(0);
}

int main() {
  int err;
  pthread_t ctid;

  // !!! We need several processes to cause context switches. Threads
  // probably also work. I don't know if the other tasks also need to
  // be doing AVX operations, but here we do.
  int nproc = sysconf(_SC_NPROCESSORS_ONLN);
  for (int i = 0; i < 2 * nproc; i++) {
    pid_t child = fork();
    if (child < 0) {
      die("fork failed", errno);
    } else if (child == 0) {
      // Exit if the parent dies.
      prctl(PR_SET_PDEATHSIG, SIGKILL, 0, 0, 0);
      doTest();
    }
  }

  // Exit after a while.
  if ((err = pthread_create(&ctid, NULL, exiter, NULL)) != 0)
    die("pthread_create exiter", err);

  // Wait for a failure.
  int status;
  if (wait(&status) < 0)
    die("wait", errno);
  if (status == 0)
    die("child unexpectedly exited with success", 0);
  fprintf(stderr, "child process failed\n");
  exit(1);
}