#include "board.h"

int board_init(board_t* board, int size){
    if ( size < 1) return 0;

    board->size = size;
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            board->data[row][col] = '.';
        }
    }
    return 1;
}

void board_print(const board_t* board){
    for (int n = 0; n < board->size; n++) printf(" %c  ", 'A' + n);
    printf("\n");
    for (int row = 0; row < board->size; row++) {
        for (int n = 0; n < row; n++) printf(" ");
        printf ("%d ", row + 1);
        for (int col = 0; col < board->size; col++) {
            printf("%c   ", board -> data[row][col]);   
        }
        printf("%d", row + 1);
        printf("\n");
    }
    for (int n = 0; n < board->size; n++) printf(" ");
    for (int n = 0; n < board->size; n++) printf("   %c", 'A' + n);
    printf("\n");
}

int board_play(board_t* board, int row, int col, char color) {
    if ( col < 0 || col >= board->size || row < 0 || row >= board->size) return 0;
    if (color != 'x' && color != 'o') return 0;

    if (board->data[row][col] != '.') return 0;
    board->data[row][col] = color; 
    
    return 1; 
}
