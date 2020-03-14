#include "word_manage_p.h"

Word word_array[WORD_NUM_MAX];
int num_of_word;

/**
 * 単語管理部を初期化する
 */
void word_initialize(void) 
{
    num_of_word = 0;
}