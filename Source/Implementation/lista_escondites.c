#include <lista_escondites.h>
#include <math.h>
#include <stdlib.h>

ListaEscondites NewListaEscondites(size_t cant) {
    ListaEscondites le;
    le.arr = MemAlloc(cant * sizeof(*le.arr));
    le.cantidad = cant;
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

    for (size_t i = 0; i < lesc->cantidad; i++) {
        if (lesc->arr[i].ocupado == false)
            return lesc->arr + i;
    }
    return NULL;
}

Escondite *SiguienteEscondite(ListaEscondites *lesc, Vector2 coords) {
    Escondite *esc = NULL;
    for (size_t i = 0; i < lesc->cantidad; i++) {
        if (lesc->arr[i].distancia_de_escondite + lesc->arr[i].coords.y <=
            coords.y)
            continue;
        if (lesc->arr[i].ocupado)
            continue;

        if (!esc || (fabsf(esc->coords.x - coords.x) >
                     fabsf(lesc->arr[i].coords.x + -coords.x)))
            esc = lesc->arr + i;
    }
    return esc;
}

void Dibujar_ListaEscondites(ListaEscondites *lesc) {
    for (size_t i = 0; i < lesc->cantidad; i++) {
        Dibujar(lesc->arr[i].dib, lesc->arr[i].coords);
    }
}
