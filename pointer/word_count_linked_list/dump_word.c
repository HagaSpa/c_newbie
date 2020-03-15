#include <stdio.h>
#include "word_manage_p.h"

/**
 * 単語の一覧をダンプする
 */
void dump_word(FILE *fp)
{
    Word *pos;
    for (pos=word_header; pos; pos=pos->next) {
        fprintf(fp, "%-20s%5d\n",
                pos->name, pos->count);
    }
}