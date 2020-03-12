#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    int size;
    printf("board size?");
    scanf("%d", &size);

    /* size * size の2次元配列を確保 */
    int (*board)[size] = malloc(sizeof(int) * size * size);
    /* 2次元配列に0から昇順に数字を入力 */
    for (int i=0; i<size; i++) {
        for (int j=0; j<size; j++) {
            board[i][j] = i * size + j;
        }
    }

    /* size * size分回して各値を表示することで、ボードを表現 */
    for (int i=0; i<size; i++) {
        for (int j=0; j<size; j++) {
            printf("%2d, ", board[i][j]);
        }
        printf("\n");
    }
}