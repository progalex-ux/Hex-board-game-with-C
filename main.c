#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "engine.h"
#include "monte_carlo.h"
#include <unistd.h>

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
    if (!board_init(&board, 7)) return 1;
    const unsigned simulations = 100;
    long available = sysconf(_SC_NPROCESSORS_ONLN);
    unsigned threads = available > 0 ? (unsigned)available : 1;
    char human, computer;
    do {
        printf("Elige tu ficha (x conecta numeros, o conecta letras) [x/o]: ");
        fflush(stdout);
        int ch = getchar();
        while (getchar() != '\n' && !feof(stdin)) {}
        human = (char)ch;
    } while (human != 'x' && human != 'o');
    computer = human == 'x' ? 'o' : 'x';
    char current = 'x';
    while (1){
        board_print(&board);
        int state;
        if (current == human) {
            if (!read_play(&board, human)) break;
        } else {
            int move = monte_carlo_move(&board, computer, simulations, threads);
            if (move < 0 || !board_play(&board, move / board.size, move % board.size, computer)) break;
            // printf("La computadora (%c) juega %c%d (%u simulaciones, %u hilos).\n", computer, 'A' + move % board.size, move / board.size + 1, simulations, threads);
        }
        state = game_state(&board);
        if (state) {
            board_print(&board);
            printf("Gana el jugador '%c'.\n", state == 1 ? 'x' : 'o');
            break;
        }
        current = current == 'x' ? 'o' : 'x';
    }
    return 0;
}
