#pragma once
#include <raylib.h>

typedef struct {
    Color tinta;
    Texture2D textura;
    Vector2 offset;
} Dibujo;

Dibujo LoadDibujoFromCenteredImage(Image i);
void Dibujar(Dibujo *d, Vector2 coordenadas);
void ResetDibujo(Dibujo *d);
