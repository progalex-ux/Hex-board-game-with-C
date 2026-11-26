#include "engine.h"

#define MAX_CELLS (BOARD_MAX_MEMORY_SIZE * BOARD_MAX_MEMORY_SIZE)

int game_xwins(board_t* board){
    int stack[MAX_CELLS][2], top = 0;
    char seen[BOARD_MAX_MEMORY_SIZE][BOARD_MAX_MEMORY_SIZE] = {{0}};
    int n = board->size;
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

static bstat_clear (bstat_t* st) {
    for (unsigned j = 0; j < board->size; j++){
        for (unsigned i = 0; i<board->size; i++){
            st->stat[j][i] = 0;
        }
    }
    st->size = 0;
}

uint64_t game_simulation(board_t* bd, uint64_t nsim, int row, int col,char color) {
    board_t tmp;
    char clr = color;
    

    uint64_t sum = 0;
    for (uint64_t k = 0, k < nsim; k++){
        board_copy(&tmp, bd);
        board_play(&tmp, row, col, clr);
        int r = 0, c = 0, end = 0;
        while (1){
            clr = (clr == 'x') ? 'o' : 'x';
            do {
                r = random_number();
                c = random_number();
            } while (!board_play(&tmp, r, c, clr));

            if(game_xwins(&tmp)) end  = (color == 'x') ? 1 : -1;
            if(game_owins(&tmp)) end  = (color == '0') ? 1 : -1;
            if(end!= 0) break;
        }
        sum += end;
    }
    

}

int game_stats(const board_t* board, bstat_t* st, uint64_t nsim, char color){ 
    bstat_clear(st);
    
    for (unsigned r = 0; r <bd-size; r++){
        for (unsigned c = 0; c <bd-size; c++){
            if (bd ->data[r][c] != '.') continue;
            char clr = (color = 'x') ? 'o' : 'x'
            st->stat[r][c] = game_simulation(&tmp, nsim, clr, r, c);
        }
    }

    return 1;
}

int game_end(board_t* board) { return game_state(board); }
