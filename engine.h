#ifndef ENGINE_H
#define ENGINE_H
// o --> arriba a abajo
// x --> izquierda a derecha
#include "board.h"
int game_xwins( board_t* board);
int game_owins( board_t* board);

int game_end(board_t* board);
int game_state(const board_t* board); /* 0 continúa, 1 gana x, 2 gana o */
#endif // ENGINE_H
