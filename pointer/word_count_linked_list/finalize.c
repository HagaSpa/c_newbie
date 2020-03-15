#include <stdlib.h>
#include "word_manage_p.h"

/**
 * 単語管理部の終了処理を行う
 */
void word_finalize(void)
{
    Word *temp;

    while (word_header != NULL) {
        temp = word_header;
        word_header = word_header->next;
        free(temp->name);
        free(temp);
    }
}