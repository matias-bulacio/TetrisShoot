#pragma once
#include <collision.h>
#include <dibujo.h>
#include <raylib.h>
#include <stdbool.h>

typedef struct {
    CollisionBox collision;
    Vector2 coords;
    Dibujo *dib;
    float distancia_de_escondite;
    bool ocupado;
} Escondite;
