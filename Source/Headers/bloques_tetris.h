
#pragma once
#include <raylib.h>
#include <tetris.h>


#define FILA 21
#define COLUMN 16
#define PIEZAS_MAX 7
#define maxY 20
#define FILAS_MAX 4
#define COLUMNAS_MAX 4

extern int board[FILA][COLUMN];
extern Color board_color[FILA][COLUMN];
extern Color color[7];
extern int bloque[PIEZAS_MAX][FILAS_MAX][COLUMNAS_MAX];
extern int DERECHA1[PIEZAS_MAX][FILAS_MAX][COLUMNAS_MAX];
extern int DERECHA2[PIEZAS_MAX][FILAS_MAX][COLUMNAS_MAX];
extern int DERECHA3[PIEZAS_MAX][FILAS_MAX][COLUMNAS_MAX];


