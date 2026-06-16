#include <collision.h>
#include <enemigos.h>
#include <estadisticas.h>
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

Vector2 coordenadas_bala = {0, -100};
bool mostrar_bala = false;
CollisionBox colisiones_bala = (CollisionBox){
    .left = -16,
    .right = 16,
    .down = 30,
    .up = -30,
};

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
        e->colisiones = (CollisionBox){
            .left = -20,
            .right = 20,
            .up = -50,
            .down = 50,
        };
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

    int movimiento_pistola = delta * 400 *
                             ((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) -
                              (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)));

    posicion_pistola += movimiento_pistola;
    if (mostrar_bala) {
        coordenadas_bala.y -= 1600 * delta;
    }

    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W) ||
        IsKeyPressed(KEY_SPACE)) {
        mostrar_bala = true;
        coordenadas_bala.x = posicion_pistola;
        coordenadas_bala.y = 520;
    }

    if (coordenadas_bala.y < -50)
        mostrar_bala = false;

    for (size_t i = 0; i < cantidad_enemigos; i++) {
        Enemigo *e = &arreglo_de_enemigos[i];
        Enemigo_Avanzar(e, 75, delta);
        if (mostrar_bala) {
            if (DetectCollision(e->colisiones, colisiones_bala, e->coordenadas,
                                coordenadas_bala)) {
                mostrar_bala = false;
                e->coordenadas.y = 2000;
            }
        }
    }

    ClearBackground(BEIGE);

    DrawRectangle(0, 500, 832, 20, ColorAlpha(WHITE, 0.8));

    Enemigo_DibujarVarios(arreglo_de_enemigos, cantidad_enemigos);

    char buf[200];
    sprintf(buf, "Vida: %u", puntos);

    if (mostrar_bala)
        DrawRectangle(coordenadas_bala.x + colisiones_bala.left,
                      coordenadas_bala.y + colisiones_bala.up,
                      colisiones_bala.right - colisiones_bala.left,
                      colisiones_bala.down - colisiones_bala.up, RED);
    DrawRectangle(posicion_pistola - 20, 550, 40, 90, DARKGRAY);
    DrawText(buf, 20, 20, 24, BLACK);
    return 1;
}
