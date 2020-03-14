#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>


/*
 * ファイルを読み込んで、１つずつ単語を返却する。
 * 
 */
int get_word(char *buf, int buf_size, FILE *fp)
{
    int len;
    int ch;

    /* 空白文字を読み飛ばす */
    while ((ch = getc(fp)) != EOF && !isalnum(ch));
    
    /* ファイルの最後ならEOFを返却 */
    if (ch == EOF) return EOF;

    /* chには単語の最初の文字が格納されているはず */
    len = 0;
    do {
        buf[len] = ch;
        len++;
        if (len >= buf_size) {
            fprintf(stderr, "word too long.\n");
            exit(1);
        }
    } while ((ch = getc(fp)) != EOF && isalnum(ch));

    buf[len] = '\0';
    return len;
}
