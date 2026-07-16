#pragma once

#include "escondite.h"
#include "lista_escondites.h"
#include <collision.h>
#include <dibujo.h>
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
    Vector2 objetivo;
    double esperar_hasta;
    Vector2 coordenadas;
	int velocidad;
    CollisionBox colisiones;
    Dibujo *dib;
	Escondite *esc;
	ListaEscondites *le;
} Enemigo;

void Enemigo_Update(Enemigo *e, float now, float frame_time);

void Enemigo_DibujarVarios(Enemigo *e, size_t cantidad);
