#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "word_manage_p.h"

static void shift_array(int index)
{
    int src; // コピー元のインデックス
    for (src=num_of_word-1; src>=index; src--) {
        word_array[src+1] = word_array[src];
    }
    num_of_word++;
}

/*
 * 文字列を複製する.
 * 処理系によってはstrdup()があるが、一応自作しておく
 * 
 */
static char *my_strdup(char *src)
{
    char *dest;
    /* 
    ここって+1する理由ある？
    srcをdestへコピーするんだから、mallocするサイズは同じでいいのでは? 
    終端文字のための1バイト？？ →　あたり
    https://teratail.com/questions/99420
    */
    dest = malloc(sizeof(char) * (strlen(src) + 1));
    strcpy(dest, src);
    return dest;
}

void add_word(char *word)
{
    int i;
    int result;

    if (num_of_word >= WORD_NUM_MAX) {
        /* 単語の数が配列の要素数を超えたら、異常終了 */
        fprintf(stderr, "too many words.\n");
        exit(1);
    }

    /* 同じ単語が見つかるまでループ */
    for (i=0; i<num_of_word; i++) {
        result = strcmp(word_array[i].name, word);
        if (result >= 0)
            break;
    }
    if (num_of_word != 0 && result == 0) {
        /* 同一の単語が見つかった */
        word_array[i].count++;
    } else {
        /* 初見の単語の場合 */
        shift_array(i);
        word_array[i].name = my_strdup(word);
        word_array[i].count = 1;
    }
}