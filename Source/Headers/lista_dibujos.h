#pragma once

#include <dibujo.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    Dibujo *d;
    int layer;
    Vector2 coords;
} MetadataDibujo;

typedef struct {
    MetadataDibujo *arr;
    size_t n;
    size_t cap;
} ListaDibujosEnCapas;

ListaDibujosEnCapas NewListaDibujosEnCapas(size_t cap);
bool ListaDibujosEnCapas_Reserve(ListaDibujosEnCapas *ldib, size_t new_cap);
bool ListaDibujosEnCapas_InsertMD(ListaDibujosEnCapas *ldib, MetadataDibujo md);
bool ListaDibujosEnCapas_Insert(ListaDibujosEnCapas *ldib, Dibujo *d, int layer,
                                Vector2 coords);
bool ListaDibujosEnCapas_Reset(ListaDibujosEnCapas *ldib);
bool ListaDibujosEnCapas_Free(ListaDibujosEnCapas *ldib);

void ListaDibujosEnCapas_Dibujar(ListaDibujosEnCapas *ldib);
