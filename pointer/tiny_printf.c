#include <stdio.h>
#include <stdarg.h>
#include <assert.h>

void tiny_printf(char *format, ...) {
  int i;
  va_list ap;

  // ポインタapをformatへ差すようにする
  va_start(ap, format);
  for (i = 0; format[i] != '\0'; i++) {
    switch (format[i]) {
      case 's':
        printf("%s ", va_arg(ap, char*)); // ポインタapからchar* で引数を取り出してポインタを進める
        break;
      case 'd':
        printf("%d ", va_arg(ap, int)); // ポインタapからintで引数を取り出してポインタを進める
        break;      
      default:
        assert(0);
    }
  }
  va_end(ap);
  putchar('\n');
}

int main(void) {
  tiny_printf("sdd", "result..", 3, 5);
  return 0;
}