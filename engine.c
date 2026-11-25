#include "engine.h"

#define MAX_CELLS (BOARD_MAX_MEMORY_SIZE * BOARD_MAX_MEMORY_SIZE)

int game_xwins(board_t* board){
    int stack[MAX_CELLS][2];
    int size = 0;
    int n = board->size;

    board_t visited;
    board_init(&visited, n);

    for (int row = 0; row < n; row++){
        if (board->data[row][0] == 'x') {
            stack[size][0] = row;
            stack[size][1] = 0;
            size++;
            visited.data[row][0] = '+';
        }
    }

    while (size > 0) {
        size--;
        int r = stack[size][0];
        int c = stack[size][1];

        if (c == n - 1) return 1;

        for (int y = -1; y <= 1; y++){
            for (int x = -1; x <= 1; x++){
                if (x == y) continue;
                int nr = r + y;
                int nc = c + x;
                if (nr < 0 || nr >= n || nc < 0 || nc >= n) continue;
                if (board->data[nr][nc] != 'x' || visited.data[nr][nc] == '+') continue;

                stack[size][0] = nr;
                stack[size][1] = nc;
                size++;
                visited.data[nr][nc] = '+';
            }
        }
    }
    return 0;
}

int game_owins(board_t* board){
    int stack[MAX_CELLS][2];
    int size = 0;
    int n = board->size;

    board_t visited;
    board_init(&visited, n);

    for (int col = 0; col < n; col++){
        if (board->data[0][col] == 'o') {
            stack[size][0] = 0;
            stack[size][1] = col;
            size++;
            visited.data[0][col] = '+';
        }
    }

    while (size > 0) {
        size--;
        int r = stack[size][0];
        int c = stack[size][1];

        if (r == n - 1) return 2;

        for (int y = -1; y <= 1; y++){
            for (int x = -1; x <= 1; x++){
                if (x == y) continue;
                int nr = r + y;
                int nc = c + x;
                if (nr < 0 || nr >= n || nc < 0 || nc >= n) continue;
                if (board->data[nr][nc] != 'o' || visited.data[nr][nc] == '+') continue;

                stack[size][0] = nr;
                stack[size][1] = nc;
                size++;
                visited.data[nr][nc] = '+';
            }
        }
    }
    return 0;
}

int game_end(board_t* board) {
    if (game_xwins(board)) {
        printf("El jugador 'x' ha ganado!\n");
        return 1;
    }
    if (game_owins(board)) {
        printf("El jugador 'o' ha ganado!\n");
        return 2;
    }
    return 0;
}
