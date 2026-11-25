#include "engine.h"

#define MAX_CELLS (BOARD_MAX_MEMORY_SIZE * BOARD_MAX_MEMORY_SIZE)

int game_xwins(board_t* board){
    int stack[MAX_CELLS][2], top = 0;
    char seen[BOARD_MAX_MEMORY_SIZE][BOARD_MAX_MEMORY_SIZE] = {{0}};
    int n = board->size;
    // 'x' conecta los bordes numerados, a izquierda y derecha
    for (int r = 0; r < n; ++r) if (board->data[r][0] == 'x') {
        stack[top][0] = r; stack[top++][1] = 0; seen[r][0] = 1;
    }
    while (top) {
        int r = stack[--top][0], c = stack[top][1];
        if (c == n - 1) return 1;
        for (int y=-1; y<=1; ++y) for (int x=-1; x<=1; ++x) {
            if (x == y) continue;
            int nr=r+y, nc=c+x;
            if (nr<0 || nr>=n || nc<0 || nc>=n || seen[nr][nc] || board->data[nr][nc]!='x') continue;
            seen[nr][nc]=1; stack[top][0]=nr; stack[top++][1]=nc;
        }
    }
    return 0;
}

int game_owins(board_t* board){
    int stack[MAX_CELLS][2], top = 0;
    char seen[BOARD_MAX_MEMORY_SIZE][BOARD_MAX_MEMORY_SIZE] = {{0}};
    int n = board->size;
    // 'o' conecta los bordes con letras, arriba y abajo
    for (int c = 0; c < n; ++c) if (board->data[0][c] == 'o') {
        stack[top][0] = 0; stack[top++][1] = c; seen[0][c] = 1;
    }
    while (top) {
        int r = stack[--top][0], c = stack[top][1];
        if (r == n - 1) return 2;
        for (int y=-1; y<=1; ++y) for (int x=-1; x<=1; ++x) {
            if (x == y) continue;
            int nr=r+y, nc=c+x;
            if (nr<0 || nr>=n || nc<0 || nc>=n || seen[nr][nc] || board->data[nr][nc]!='o') continue;
            seen[nr][nc]=1; stack[top][0]=nr; stack[top++][1]=nc;
        }
    }
    return 0;
}

int game_state(const board_t* board){
    board_t copy = *board;
    if (game_xwins(&copy)) return 1;
    if (game_owins(&copy)) return 2;
    return 0;
}

int game_end(board_t* board) { return game_state(board); }
