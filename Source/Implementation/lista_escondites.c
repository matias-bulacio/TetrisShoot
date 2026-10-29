#include <lista_escondites.h>
#include <math.h>
#include <stdlib.h>

ListaEscondites NewListaEscondites(size_t n) {
    ListaEscondites le;
    le.arr = MemAlloc(n * sizeof(*le.arr));
    le.n = n;
    return le;
}

void FreeListaEscondites(ListaEscondites *lesc) {
    if (!lesc)
        return;
    if (!lesc->arr)
        return;

    MemFree(lesc->arr);
    lesc->arr = NULL;
}

Escondite *PrimerEsconditeLibre(ListaEscondites *lesc) {
    if (!lesc)
        return NULL;

    if (!lesc->arr)
        return NULL;

    for (size_t i = 0; i < lesc->n; i++) {
        if (lesc->arr[i].occupied == false)
            return lesc->arr + i;
    }
    return NULL;
}

Escondite *SiguienteEscondite(ListaEscondites *lesc, Vector2 coord) {
    Escondite *esc = NULL;
    for (size_t i = 0; i < lesc->n; i++) {
        if (lesc->arr[i].standing_distance + lesc->arr[i].coord.y <= coord.y)
            continue;
        if (lesc->arr[i].occupied)
            continue;

        if (!esc || (fabsf(esc->coord.x - coord.x) >
                     fabsf(lesc->arr[i].coord.x + -coord.x)))
            esc = lesc->arr + i;
    }
    return esc;
}

void Dibujar_ListaEscondites(ListaEscondites *lesc) {
    for (size_t i = 0; i < lesc->n; i++) {
        Dibujar(lesc->arr[i].dib, lesc->arr[i].coord);
    }
}
