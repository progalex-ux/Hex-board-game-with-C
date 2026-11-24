#ifndef BOARD_H // se va a definir BOARD_H si no estaba definido previamente
#define BOARD_H // se define BOARD_H
// es un macro que evita que el contenido del archivo se incluya más de una vez en un mismo archivo fuente
// la guarda funciona para evitar errores de redefinición de clases, funciones o variables cuando se incluyen
// múltiples veces el mismo archivo de encabezado en un proyecto.

#include <stdio.h>

#define BOARD_MAX_MEMORY_SIZE 26 // tamaño máximo del tablero

typedef struct {
    int size; // tamaño del tablero
    char data[BOARD_MAX_MEMORY_SIZE][BOARD_MAX_MEMORY_SIZE]; // datos del tablero
} board_t;


int board_init (board_t* board, int size);
void board_print(const board_t* board); // función para imprimir el tablero
int board_play(board_t* board, int row, int col, char color); // función para colocar una ficha en el tablero

#endif // BOARD_H

/*
     A  B  C  D  E  F  G
1   .  .  .  .  .  .  .
2    .  .  .  .  .  .  .
3      .  .  .  0  0  .  .
4       .  .  0  x  0  .  .
5        .  .  0  0  .  .  .
6         .  .  .  .  .  .  .
7          .  .  .  .  .  .  .

    .  .  .  .  .  .  .
    .  .  .  .  .  .  .
    .  .  .  0  0  .  .
    .  .  0  x  0  .  .
    .  .  0  0  .  .  .
    .  .  .  .  .  .  .
    .  .  .  .  .  .  .

*/
