#include <escape.h>
#include <raylib.h>
#include <stdlib.h>

ListaEscapes NewListaEscapes(size_t n) {
    ListaEscapes lexit;
    lexit.arr = MemAlloc(n * sizeof(*lexit.arr));
    lexit.n = n;
    return lexit;
}

void FreeListaEscapes(ListaEscapes *lexit) {
    if (!lexit)
        return;
    if (!lexit->arr)
        return;

    MemFree(lexit->arr);
    lexit->arr = NULL;
}

Escape *MejorEscape(ListaEscapes *lexit, int x) {
    Escape *exit = NULL;
    for (size_t i = 0; i < lexit->n; i++) {
        if (!exit || (abs(exit->x - x) > abs(lexit->arr[i].x - x)))
            exit = lexit->arr + i;
    }
    return exit;
}
