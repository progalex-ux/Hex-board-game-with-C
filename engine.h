#ifndef ENGINE_H
#define ENGINE_H
// o --> arriba a abajo
// x --> izquierda a derecha
#include "board.h"
int game_xwins( board_t* board);
int game_owins( board_t* board);

int game_end(board_t* board);
#endif // ENGINE_H