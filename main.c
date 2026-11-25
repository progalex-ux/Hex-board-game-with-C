#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "engine.h"

#define BUFLEN 128

int str_to_coord(const char* str, int* colc, int* row){
    int c, r;
   
    if (str[0] >= 'a' && str[0] <= 'z') c = str[0] - 'a';
    else if (str[0] >= 'A' && str[0] <= 'Z') c = str[0] - 'A';
    else return 0;

    if(str[1] == '0') return 0; // no se permiten filas con 0 al inicio

    const char* num = (char*)str + 1;
    r = atoi(num);
    if ( r == 0) return 0; 
    *colc = c;
    *row = r - 1;
    return 1;
}

int streq (const char* str1, const char* str2){
    if ( strcmp(str1, str2) == 0) return 1;
    return 0;
}

int read_play(board_t* board, char player){
    char buffer[BUFLEN];
    int col, row;
    while (1){
        printf("Juega %c: ", player);
        fflush(stdout);
        fgets(buffer, BUFLEN, stdin);
        if (streq(buffer, "exit\n")) return 0;
        if (streq(buffer, "quit\n")) return 0;
        if (!str_to_coord(buffer, &col, &row)) continue;
        if (!board_play(board, row, col, player)) continue;
        break;
    }
    return 1;
}

int main(){
    board_t board;
    board_init(&board, 7);

    char player = 'x';
    
    while (1){
        board_print(&board);
        if (!read_play(&board, player)) break;
        if (game_end(&board)) {
            board_print(&board);
            break;
        }
        player = (player == 'x') ? 'o' : 'x';
    }
    return 0;
}