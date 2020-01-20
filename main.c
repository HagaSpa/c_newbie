#include <stdio.h>

int main(void) {
  /*

  int a;  // 21845 って毎回出るんだけどなに？
  型によって確保されたメモリに入れられる値が決まっている？？

  結論：
  全然関係なくて、ただのマシン上のメモリを使用していたゴミが21845なだけ。コンテナで起動させてるから、毎回同じなのかも？
  ⇨ https://www.kushiro-ct.ac.jp/yanagawa/C-2015/06-0430/index.html
  ⇨ コンテナのメモリ領域ってどうなってんの？

  */
  int a;
  a = 10;
  printf("aのアドレス: %p \n", &a);

  int *p;
  p = &a;
  printf("pのアドレス: %p \n", p);
  printf("pの値: %d \n", *p);
  printf("pのポインタアドレス: %p \n", *&p);
  return 0;
}