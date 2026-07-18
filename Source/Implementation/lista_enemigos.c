#include <lista_enemigos.h>

ListaEnemigos NewListaEnemigos(size_t n) {
    ListaEnemigos lenem;
    lenem.arr = MemAlloc(sizeof(*lenem.arr) * n);
    lenem.n = n;
    return lenem;
}

void Dibujar_ListaEnemigos(ListaEnemigos *lenem) {
    for (size_t i = 0; i < lenem->n; i++) {
        Enemigo *e = &lenem->arr[i];
        if (e->estado != ENEM_STATE_NULL && e->estado != ENEM_STATE_INACTIVO &&
            e->estado != ENEM_STATE_OUT)
            Dibujar(e->dib, e->coordenadas);
    }
}

void Update_ListaEnemigos(ListaEnemigos *lenem, float now, float frame_time) {
    for (size_t i = 0; i < lenem->n; i++) {
        Enemigo *e = &lenem->arr[i];
        Enemigo_Update(e, now, frame_time);
    }
}

void ListaEnemigos_ResetOutOfBounds(ListaEnemigos *lenem, int max_y) {
    for (size_t i = 0; i < lenem->n; i++) {
        if (lenem->arr[i].coordenadas.y > max_y)
            Enemigo_Reset(lenem->arr + i);
    }
}
