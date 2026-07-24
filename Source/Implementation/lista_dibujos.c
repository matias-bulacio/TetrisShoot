#include <lista_dibujos.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

ListaDibujosEnCapas NewListaDibujosEnCapas(size_t cap) {
    ListaDibujosEnCapas ldib;
    ldib.n = 0;
    ldib.arr = MemAlloc(cap * sizeof(*ldib.arr));
    ldib.cap = cap;
    return ldib;
}

bool ListaDibujosEnCapas_Reserve(ListaDibujosEnCapas *ldib, size_t new_cap) {
    if (!ldib)
        return false;
    if (!ldib->arr) {
        ldib->arr = MemAlloc(new_cap * sizeof(*ldib->arr));
    } else {
        MetadataDibujo *p = MemRealloc(ldib->arr, new_cap * sizeof(*ldib->arr));
        if (p == NULL)
            return false;

        ldib->arr = p;
    }
    if (ldib->n > new_cap)
        ldib->n = new_cap;
    ldib->cap = new_cap;
    return ldib->arr != NULL;
}

bool ListaDibujosEnCapas_InsertMD(ListaDibujosEnCapas *ldib,
                                  MetadataDibujo md) {
    size_t i = 0;
    if (!ldib)
        return false;
    if (ldib->n >= ldib->cap) {
        bool r = ListaDibujosEnCapas_Reserve(ldib, ldib->cap * 2);
        if (r)
            goto insert;
        r = ListaDibujosEnCapas_Reserve(ldib, ldib->cap + 1);
        if (!r)
            return false;
        goto insert;
    }
insert:
    for (i = 0; i < ldib->n; i++) {
        if (ldib->arr[i].layer > md.layer)
            break;
    }
    memmove(&ldib->arr[i + 1], &ldib->arr[i],
            (sizeof(*ldib->arr) * (ldib->n - i)));
    ldib->arr[i] = md;
    ldib->n++;
    return true;
}

bool ListaDibujosEnCapas_Insert(ListaDibujosEnCapas *ldib, Dibujo *d, int layer,
                                Vector2 coords) {
    return ListaDibujosEnCapas_InsertMD(ldib, (MetadataDibujo){
                                                  .d = d,
                                                  .layer = layer,
                                                  .coords = coords,
                                              });
}

bool ListaDibujosEnCapas_Reset(ListaDibujosEnCapas *ldib) {
    if (!ldib)
        return false;
    ldib->n = 0;
    return true;
}

bool ListaDibujosEnCapas_Free(ListaDibujosEnCapas *ldib) {
    if (!ldib)
        return false;
    MemFree(ldib->arr);
    return true;
}

void ListaDibujosEnCapas_Dibujar(ListaDibujosEnCapas *ldib) {
    for (size_t i = 0; i < ldib->n; i++) {
        Dibujar(ldib->arr[i].d, ldib->arr[i].coords);
    }
}
