#include <stdio.h>

int main(void) {
    // intは4バイト
    int hoge = 0x12345678;
    // int型のポインタをキャストして、unsgned char(1バイト) へ格納
    unsigned char *hoge_p = (unsigned char*) &hoge;

    // 先頭から1バイトずつ表示
    printf("%x\n", hoge_p[0]);
    printf("%x\n", hoge_p[1]);
    printf("%x\n", hoge_p[2]);
    printf("%x\n", hoge_p[3]);

    return 0;
}