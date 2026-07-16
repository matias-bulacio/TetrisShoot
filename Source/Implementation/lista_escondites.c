#include <lista_escondites.h>
#include <stdlib.h>

ListaEscondites NewListaEscondites(size_t cant) {
    ListaEscondites le;
    le.arr = calloc(cant, sizeof(*le.arr));
    le.cantidad = cant;
    return le;
}

void FreeListaEscondites(ListaEscondites *le) { free(le->arr); }

Escondite *PrimerEsconditeLibre(ListaEscondites *le) {
    for (size_t i = 0; i < le->cantidad; i++) {
        if (le->arr[i].ocupado == false)
            return le->arr + i;
    }
    return NULL;
}

Escondite *PrimerEsconditeLibreDetrasDeY(ListaEscondites *le, int min_y) {
    for (size_t i = 0; i < le->cantidad; i++) {
        if (le->arr[i].zona_escondida.y + le->arr[i].coordinates.y <= min_y)
            continue;
        if (le->arr[i].ocupado == false)
            return le->arr + i;
    }
    return NULL;
}
