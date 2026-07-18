#pragma once
#include <escondite.h>
#include <stddef.h>

typedef struct {
    Escondite *arr;
    size_t cantidad;
} ListaEscondites;

ListaEscondites NewListaEscondites(size_t cant);
void FreeListaEscondites(ListaEscondites *le);
Escondite *PrimerEsconditeLibre(ListaEscondites *le);
Escondite *SiguienteEscondite(ListaEscondites *le, Vector2 coords);

void Dibujar_ListaEscondites(ListaEscondites *lesc);
