/* 
再起呼び出しを使って、コマンドライン引数で与えられた数字から順列の全ての組み合わせを表示する。

./permutation 5 3
*/

#include <stdio.h>

#define N_MAX (100)

/*数字を使用したら、その添字の要素を1にする */
int used_flag[N_MAX + 1];

int result[N_MAX];
int n;
int r;

void print_result(void) {
  int i;
  
  for (i = 0; i < r; i++) {
    printf("%d ", result[i]);
  }
  
  printf("\n");
}

void permutation(int nth) {
  int i;
  
  if (nth == r) {
    print_result();
    return;
  }

  for (i = 1; i <= n; i++) {
    if (used_flag[i] == 0) {
      result[nth] = i;
      used_flag[i] = 1;
      permutation(nth + 1);
      /* ここが実行されるタイミングは25ステップ目がTrueのとき、return;が実行され、1つ前の再起ループに戻って実行される */
      used_flag[i] = 0;
    }
  }
}

int main(int argc, char **argv) {
  sscanf(argv[1], "%d", &n);
  sscanf(argv[2], "%d", &r);
  permutation(0);
}