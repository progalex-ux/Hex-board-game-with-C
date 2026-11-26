#ifndef ENGINE_H
#define ENGINE_H
// o --> arriba a abajo
// x --> izquierda a derecha
#include <stdint.h>
#include "board.h"

typedef struct {
    unsigned size;
    int64_t stat[BOARD_MAX_SIZE][BOARD_MAX_SIZE]
} bstat_t;

int game_xwins(const board_t* board);
int game_owins(const board_t* board);

int game_end(board_t* board);
int game_stats(const board_t* board, bstat_t* st); 
#endif // ENGINE_H
