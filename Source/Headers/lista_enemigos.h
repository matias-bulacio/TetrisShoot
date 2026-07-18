#pragma once

#include <enemigos.h>
typedef struct {
    Enemigo *arr;
    size_t n;
} ListaEnemigos;

ListaEnemigos NewListaEnemigos(size_t n);
void Dibujar_ListaEnemigos(ListaEnemigos *lenem);
void Update_ListaEnemigos(ListaEnemigos *lenem, float now, float frame_time);
void ListaEnemigos_ResetOutOfBounds(ListaEnemigos *lenem, int max_y);
