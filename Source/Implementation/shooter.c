#include <enemigos.h>
#include <puntos.h>
#include <raylib.h>
#include <shooter.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

Enemigo *arreglo_de_enemigos;
Image image;
Texture2D texture;
size_t cantidad_enemigos = 5;

int posicion_pistola = 416;

int setup_shooter() {
    if (IsTextureValid(texture)) {
        UnloadTexture(texture);
    }
    if (IsImageValid(image)) {
        UnloadImage(image);
    }

    image = LoadImage("Resources/Animals/tiger.png");
    ImageResizeNN(&image, 128, 128);
    texture = LoadTextureFromImage(image);

    if (arreglo_de_enemigos == NULL)
        free(arreglo_de_enemigos);
    cantidad_enemigos = 5;

    arreglo_de_enemigos =
        calloc(cantidad_enemigos, sizeof(*arreglo_de_enemigos));

    if (arreglo_de_enemigos == NULL) {
        return -1; // Error
    }

    for (size_t i = 0; i < cantidad_enemigos; i++) {
        Enemigo *e = &arreglo_de_enemigos[i];
        e->coordenadas.y = 0;
        e->coordenadas.x = 64 + 176 * i;
        e->textura = &texture;
    }
    return 0;
}

int shooter(bool setup) {
	float delta = GetFrameTime();
    if (setup) { // Setting up
        int r = setup_shooter();
        if (r != 0)
            return r;
    }
    for (size_t i = 0; i < cantidad_enemigos; i++) {
        Enemigo_Avanzar(&arreglo_de_enemigos[i], 75, delta);
    }

    int movimiento_pistola = delta * 400 * ((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) -
                                    (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)));
	 posicion_pistola += movimiento_pistola;

    ClearBackground(BEIGE);

    DrawRectangle(0, 500, 832, 20, ColorAlpha(WHITE, 0.8));

    Enemigo_DibujarVarios(arreglo_de_enemigos, cantidad_enemigos);

    char buf[200];
    sprintf(buf, "Puntos: %u", puntos);

    DrawText(buf, 20, 20, 24, BLACK);

    DrawRectangle(posicion_pistola - 16, 550, 32, 90, DARKGRAY);
    return 1;
}
