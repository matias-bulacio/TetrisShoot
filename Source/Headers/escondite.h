#pragma once
#include <collision.h>
#include <dibujo.h>
#include <raylib.h>
#include <stdbool.h>

typedef struct {
    CollisionBox collision;
    Vector2 coordinates;
    Dibujo *dib;
    Vector2 zona_escondida;
    bool ocupado;
} Escondite;
