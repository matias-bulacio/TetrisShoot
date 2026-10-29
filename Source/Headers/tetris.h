#pragma once

#include <stdbool.h>
int tetris(bool setup);
enum Pieza {
    PIEZA_CUADRADO,
    PIEZA_LINEA,
    PIEZA_T,
    PIEZA_L_INVERTIDA,
    PIEZA_L,
    PIEZA_Z,
    PIEZA_Z_INVERTIDA,
};
