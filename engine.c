#include "engine.h"

int game_xwins( board_t* board){
    int stack[26][26];
    int size = 0; // Numero de elementos de la pila
    int n = board->size;

    board_t mk;
    board_init(&mk, board -> size);

    for (unsigned i = 0; i < board->size; i++){
        if (board->data[i][0] == 'x') {
            stack[size][0] = i;
            stack[size][1] = 0;
            size++;
        }
    }

    while (size > 0) {
        size --;
        int r = stack[size][0];
        int c = stack[size][1];

        // Marcamos esta posición para no volverla a ingresar
        mk.data[r][c] = '+';

        for(int y = -1; y <= 1; y++){
            for(int x = -1; x <= 1; x++){
                if ( x == y) continue;
                if (r+y < 0 || r+y >= board->size) continue;
                if (c+x < 0 || c+x >= board->size) continue;
                if (mk.data[r+y][c+x] == 'x') continue;
                if (board->data[r+y][c+x] == 'x'){
                    if (c+x == n-1) return 1; // Si llegamos a la última columna, 'x' gana
                    stack[size][0] = r+y;
                    stack[size][1] = c+x;
                    size++;
                }
            }
        }

    }
    return 0;
};

int game_owins( board_t* board){
    int stack[26][26];
    int size = 0; // Numero de elementos de la pila
    int n = board->size;

    board_t mk;
    board_init(&mk, board -> size);

    for (unsigned i = 0; i < board->size; i++){
        if (board->data[0][i] == 'o') {
            stack[size][0] = 0;
            stack[size][1] = i;
            size++;
        }
    }

    while (size > 0) {
        size --;
        int r = stack[size][0];
        int c = stack[size][1];

        // Marcamos esta posición para no volverla a ingresar
        mk.data[r][c] = '+';

        for(int y = -1; y <= 1; y++){
            for(int x = -1; x <= 1; x++){
                if ( x == y) continue;
                if (r+y < 0 || r+y >= board->size) continue;
                if (c+x < 0 || c+x >= board->size) continue;
                if (mk.data[r+y][c+x] == 'x') continue;
                if (board->data[r+y][c+x] == 'x'){
                    if (c+x == n-1) return 2; // Si llegamos a la última columna, 'o' gana
                    stack[size][0] = r+y;
                    stack[size][1] = c+x;
                    size++;
                }
            }
        }

    }
    return 0;
};

int game_end(board_t* board) {
    if (game_xwins(board)) {
        printf("El jugador 'x' ha ganado!\n");
        return 1; // 'x' gana
    }
    if (game_owins(board)) {
        printf("El jugador 'o' ha ganado!\n");
        return 2; // 'o' gana
    }
    return 0; // El juego continúa
}