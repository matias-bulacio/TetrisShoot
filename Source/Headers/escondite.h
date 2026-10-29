#pragma once
#include <collision.h>
#include <dibujo.h>
#include <raylib.h>
#include <stdbool.h>

typedef struct {
    CollisionBox col;
    Vector2 coord;
    Dibujo *dib;
    float standing_distance;
    bool occupied;
} Escondite;
