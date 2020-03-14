#include <stdlib.h>
#include "word_manage_p.h"

/**
 * 単語管理部の終了処理を行う
 */
void word_finalize(void)
{
    int i;
    for (i=0; i<num_of_word; i++) {
        free(word_array[i].name);
    }
    num_of_word = 0;
}