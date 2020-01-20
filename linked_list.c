#include <stdlib.h>
#include <stdio.h>

// 連結リストの構造体
struct linked_list {
  int data;
  struct linked_list *next;
};

/*
http://web.wakayama-u.ac.jp/~tac/pointer/
*/
void main(void) {
  struct linked_list *root;
  struct linked_list *p;

  // mallocの仕様でメモリ確保できなかったらNULLが来る
  p = malloc(sizeof(struct linked_list));
  if (p != NULL) {   
    // rootをpを使って初期化
    root = p;
    // mallocにより動的に確保したメモリ領域はすでに値が入っているので、初期化
    p->data = 0;
    p->next = NULL;
  }

  // 2個目のnodeを追加
  p = malloc(sizeof(struct linked_list));
  if (p != NULL) {
    root->next = p;
    p->data = 1;
    p->next = NULL;
  }

  // 3個目のnodeを1と2の間に追加
  p = malloc(sizeof(struct linked_list));
  if (p != NULL) {
    p->data = 2;
    p->next = root->next;
    root->next = p;
  }

}