#ifndef MONTE_CARLO_H
#define MONTE_CARLO_H
#include "board.h"

// Devuelve el índice lineal de la mejor casilla para ai_player
int monte_carlo_move(const board_t *board, char ai_player, unsigned simulations, unsigned threads);

#endif
