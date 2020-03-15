#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "word_manage_p.h"

/*
 * 文字列を複製する.
 * 処理系によってはstrdup()があるが、一応自作しておく
 * 
 */
static char *my_strdup(char *src)
{
    char *dest;
    dest = malloc(sizeof(char) * (strlen(src) + 1));
    strcpy(dest, src);
    return dest;
}

/*
 * 新しいWord構造体を生成する
 */
static Word *create_word(char *name)
{
    Word *new_word;
    new_word = malloc(sizeof(Word));
    new_word->name = my_strdup(name);
    new_word->count = 1;
    new_word->next = NULL;
    return new_word;
}

/*
 * 単語を追加する 
 */
void add_word(char *word)
{
    Word *pos;
    Word *prev; /*posのあとを１つ遅れてついていくポインタ*/
    Word *new_word;
    int result;

    prev = NULL;
    for (pos = word_header; pos != NULL; pos = pos->next) {
        result = strcmp(pos->name, word); /* strcmpは文字コードの値で大小を返却するため、ソート時の文字コード判定を実現 */
        if (result >= 0)
            break;
        prev = pos;
    }

    if (word_header != NULL && result == 0) {
        /* 同一の単語が見つかった */
        pos->count++;
    } else {
        new_word = create_word(word);
        if (prev == NULL) {
            /* 先頭に挿入 */
            /* prev==NULL のときは、40ステップ目が一回しかループしなかったとき、つまり最初の単語 */
            new_word->next = word_header;
            word_header = new_word;
        } else {
            new_word->next = pos;
            prev->next = new_word;
        }
    }
}