#include <stdio.h>
#include <stdlib.h>
#include "get_word.h"
#include "word_manage.h"

#define WORD_LEN_MAX (1204)

int main(int argc, char **argv)
{
    char buf[WORD_LEN_MAX];
    FILE *fp;

    if (argc == 1) {
        fp = stdin;
    } else {
        fp = fopen(argv[1], "r");
        if (fp == NULL) {
            fprintf(stderr, "%s:%s can not opne, \n", argv[0], argv[1]);
            exit(1);
        }
    }

    /* Initialize */
    word_initialize();

    /* reading file, add word */
    while (get_word(buf, WORD_LEN_MAX, fp) != EOF) {
        add_word(buf);
    }
    
    /* output word counts */
    dump_word(stdout);

    /* Finalize */
    word_finalize();

    return 0;
}