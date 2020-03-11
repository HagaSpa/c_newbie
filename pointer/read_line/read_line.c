#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define ALLOC_SIZE (256)

/*
 * 行を読み込むバッファ領域.必要に応じて拡張される 
 */
static char *st_line_buffer = NULL;

/*
 * st_line_bufferの先に割り当てられている領域のサイズ
 */
static int st_current_buffer_size = 0;

/* 
 * st_line_bufferの中で、現在文字が格納されているサイズ 
 * 要は文字数？
 */
static int st_current_used_size = 0;

/*
 * st_line_bufferの末尾に1文字追加する
 * 必要次第で、st_line_bufferの先の領域を拡張する
 * 
 * ch: 追加する1文字
 */
static void add_character(int ch)
{
    /*
     * st_current_used_sizeは必ず1つずつ増える。
     * その確認
     */
    assert(st_current_buffer_size >= st_current_used_size);

    /*
     * st_current_buffer_sizeに、st_current_used_sizeが追いついたら、バッファを拡張する
     */
    if (st_current_buffer_size == st_current_used_size)
    {
        st_line_buffer = realloc(st_line_buffer,
                                 (st_current_buffer_size + ALLOC_SIZE) * sizeof(char));
        st_current_buffer_size += ALLOC_SIZE;
    }

    /* バッファの末尾に、引数で渡された文字を追加 */
    st_line_buffer[st_current_used_size] = ch;
    st_current_used_size++;
}

/*
 * fpから1行読み込む。ファイルの末尾にきたらNULLを返す。
 */
char *read_line(FILE *fp)
{
    int ch;
    char *ret;

    st_current_used_size = 0;
    while ((ch = getc(fp)) != EOF) {
        if (ch == '\n') {
            add_character('\0');
            break;
        }
        add_character(ch);
    }

    if (ch == EOF) {
        if (st_current_used_size > 0) {
            /* 最後の行の後に改行がなかった場合 */
            add_character('\0');
        } else {
            return NULL;   
        }
    }
    ret = malloc(sizeof(char) * st_current_used_size);
    strcpy(ret, st_line_buffer);
}

/*
 * バッファを開放する。呼び出す必要はないが一応
 */
void free_buffer(void)
{
    free(st_line_buffer);
    st_line_buffer = NULL;
    st_current_buffer_size = 0;
    st_current_used_size = 0;
}