#include <dibujo.h>

Dibujo LoadDibujoFromCenteredImage(Image i) {
    Dibujo d;
    d.textura = LoadTextureFromImage(i);
    d.tinta = WHITE;
    d.offset = (Vector2){
        .x = -i.width / 2.,
        .y = -i.height / 2.,
    };
    return d;
}

void Dibujar(Dibujo *d, Vector2 coordenadas) {
    DrawTexture(d->textura, d->offset.x + coordenadas.x,
                d->offset.y + coordenadas.y, d->tinta);
}

void ResetDibujo(Dibujo *d) {
    if (IsTextureValid(d->textura))
        UnloadTexture(d->textura);
}
