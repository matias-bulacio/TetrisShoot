#pragma once

#include <collision.h>
#include <dibujo.h>
#include <escape.h>
#include <escondite.h>
#include <lista_escondites.h>
#include <raylib.h>
#include <stddef.h>
typedef enum {
    ENEM_STATE_NULL,
    ENEM_STATE_INACTIVO,
    ENEM_STATE_ESCONDIDO,
    ENEM_STATE_CORRIENDO_X,
    ENEM_STATE_CORRIENDO_Y,
    ENEM_STATE_OUT
} Enemigo_Estado;

typedef struct {
    Enemigo_Estado estado;
    Vector2 goal;
    double wait_until;
    Vector2 coord;
    int speed;
    int min_speed;
    int max_speed;
    CollisionBox col;
    Dibujo *dib;
    Escondite *esc;
    ListaEscondites *lesc;
    ListaEscapes *lexit;
} Enemigo;

void Enemigo_Update(Enemigo *e, float now, float frame_time);

void Enemigo_Reset(Enemigo *e);
