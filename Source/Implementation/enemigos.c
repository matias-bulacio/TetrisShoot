#include <enemigos.h>
#include <stddef.h>

void Enemigo_Avanzar(Enemigo *e, int velocidad, float frame_time) {
    e->coordenadas.y += velocidad * frame_time;
}

void Enemigo_DibujarVarios(Enemigo *earr, size_t cantidad) {
    for (size_t i = 0; i < cantidad; i++) {
        Enemigo *e = &earr[i];
        DrawTexture(*e->textura, e->coordenadas.x - 64, e->coordenadas.y - 64,
                    WHITE);
    }
}
