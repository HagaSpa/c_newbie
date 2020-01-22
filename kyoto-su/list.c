/*
http://www.cc.kyoto-su.ac.jp/~yamada/ap/list.html
*/
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS     1       /* 成功 */
#define FAILURE     0       /* 失敗 */


typedef int data_t;
typedef struct nodetag {
  data_t data;
  struct nodetag *next;
} node_t;

/* 線形リストを表現する型 */
typedef node_t *list_t;

/*
新しいノード構造体のための、ヒープ領域を割り当てる
*/
node_t *nodeNew(data_t dt, node_t *nxt) {
  node_t *ndPtr = malloc(sizeof(node_t));
  if (ndPtr == NULL) {
    return NULL;
  }
  ndPtr->data = dt;
  ndPtr->next = nxt;
  return ndPtr;
}

/*
渡されたポインタを使用して、連結リストの中身(data)を表示する
*/
void listPrint(node_t *ndPtr) {
  /*
  実際のリストではなくて、ポインタが来る
  ⇨ nextで潜っていくため「最大ループ数が定義されたfor」ではなく、whileでループ
  ⇨ リスト最後のnodeがNULLにしている前提
  */
  while (ndPtr != NULL) {
    printf("%d\n", ndPtr->data);
    ndPtr = ndPtr->next;
  }
}

/*
渡されたポインタを使用して、連結リストの要素数（node数）を返却する
*/
int nodeCount(node_t *ndPtr) {
  int count = 0;
  while (ndPtr != NULL) {
    ++count;
    ndPtr = ndPtr->next;
  } 
  return count;
}


void main(void) {
  node_t nd1, nd2, nd3;
  node_t *p;

  nd1.data = 1;
  nd1.next = &nd2;
  nd2.data = 2;
  nd2.next = &nd3;
  nd3.data = 3;
  nd3.next = NULL;

  p = &nd1;
  printf("%d\n", p->data); // *pはnd1を指している
  p = p->next;
  printf("%d\n", p->data); // *pはnd2を指している. p->next->data と同等 
  p = p->next;
  printf("%d\n", p->data); // *pはnd3を指している. p->next->next->data と同等

  /* ヒープ領域を割り当てる関数のテスト */
  node_t *ndPtr;
  ndPtr = nodeNew(10, NULL);

  /* 線形リスト */
  list_t list;

}