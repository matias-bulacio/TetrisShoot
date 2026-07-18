#include <lista_escondites.h>
#include <math.h>
#include <stdlib.h>

ListaEscondites NewListaEscondites(size_t cant) {
    ListaEscondites le;
    le.arr = MemAlloc(cant * sizeof(*le.arr));
    le.cantidad = cant;
    return le;
}

void FreeListaEscondites(ListaEscondites *le) { MemFree(le->arr); }

Escondite *PrimerEsconditeLibre(ListaEscondites *le) {
    for (size_t i = 0; i < le->cantidad; i++) {
        if (le->arr[i].ocupado == false)
            return le->arr + i;
    }
    return NULL;
}

Escondite *SiguienteEscondite(ListaEscondites *le, Vector2 coords) {
    Escondite *esc = NULL;
    for (size_t i = 0; i < le->cantidad; i++) {
        if (le->arr[i].zona_escondida.y + le->arr[i].coordinates.y <= coords.y)
            continue;
        if (le->arr[i].ocupado)
            continue;

        if (!esc ||
            (fabsf(esc->zona_escondida.x + esc->coordinates.x - coords.x) >
             fabsf(le->arr[i].zona_escondida.x + le->arr[i].coordinates.x +
                   -coords.x)))
            esc = le->arr + i;
    }
    return esc;
}

void Dibujar_ListaEscondites(ListaEscondites *lesc) {
    for (size_t i = 0; i < lesc->cantidad; i++) {
        Dibujar(lesc->arr[i].dib, lesc->arr[i].coordinates);
    }
}
