#include <escape.h>
#include <raylib.h>
#include <stdlib.h>

ListaEscapes NewListaEscapes(size_t n) {
    ListaEscapes lexits;
    lexits.arr = MemAlloc(n * sizeof(*lexits.arr));
    lexits.n = n;
    return lexits;
}

void FreeListaEscapes(ListaEscapes *lexits) {
    if (!lexits)
        return;
    if (!lexits->arr)
        return;

    MemFree(lexits->arr);
    lexits->arr = NULL;
}

Escape *MejorEscape(ListaEscapes *lexits, int x) {
    Escape *exit = NULL;
    for (size_t i = 0; i < lexits->n; i++) {
        if (!exit || (abs(exit->x - x) > abs(lexits->arr[i].x - x)))
            exit = lexits->arr + i;
    }
    return exit;
}
