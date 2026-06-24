#include <collision.h>
#include <enemigos.h>
#include <estadisticas.h>
#include <raylib.h>
#include <shooter.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <resources.h>
#include <stdlib.h>

Image image_pistola;
Image image_bala;
Image image_enemigo;
Texture2D textura_pistola;
Texture2D textura_bala;
Texture2D textura_enemigo;

Enemigo *arreglo_de_enemigos;
size_t cantidad_enemigos = 5;

Vector2 coordenadas_bala = {0, -100};
bool mostrar_bala = false;
CollisionBox colisiones_bala = (CollisionBox){
    .left = -21,
    .right = 21,
    .down = 21,
    .up = -21,
};

// SCREEN_WIDTH/2
int posicion_pistola = 416;

// Una función de setup que se llama la primera vez en cada escena
int setup_shooter() {
    if (IsTextureValid(textura_pistola)) {
        UnloadTexture(textura_pistola);
    }
    if (IsImageValid(image_pistola)) {
        UnloadImage(image_pistola);
    }
    image_pistola = Resources_LoadImage("Resources/Shooter/pistol.png");
    ImageResizeNN(&image_pistola, 45, 180);
    textura_pistola = LoadTextureFromImage(image_pistola);

    if (IsTextureValid(textura_bala)) {
        UnloadTexture(textura_bala);
    }
    if (IsImageValid(image_bala)) {
        UnloadImage(image_bala);
    }
    image_bala = Resources_LoadImage("Resources/Shooter/bala.png");
    ImageResizeNN(&image_bala, colisiones_bala.right - colisiones_bala.left,
                  colisiones_bala.down - colisiones_bala.up);
    textura_bala = LoadTextureFromImage(image_bala);

    if (IsTextureValid(textura_enemigo)) {
        UnloadTexture(textura_enemigo);
    }
    if (IsImageValid(image_enemigo)) {
        UnloadImage(image_enemigo);
    }
    image_enemigo = Resources_LoadImage("Resources/Animals/tiger.png");
    ImageResizeNN(&image_enemigo, 128, 128);
    textura_enemigo = LoadTextureFromImage(image_enemigo);

    if (arreglo_de_enemigos == NULL)
        free(arreglo_de_enemigos);
    cantidad_enemigos = 5;

    arreglo_de_enemigos =
        calloc(cantidad_enemigos, sizeof(*arreglo_de_enemigos));

    if (arreglo_de_enemigos == NULL) {
        return -1; // Error
    }

    // TODO: Mover estos números mágicos a una configuración
    for (size_t i = 0; i < cantidad_enemigos; i++) {
        Enemigo *e = &arreglo_de_enemigos[i];
        e->coordenadas.y = 0;
        e->coordenadas.x = 64 + 176 * i;
        e->textura = &textura_enemigo;
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
    if (setup) {
        int r = setup_shooter();
        if (r != 0)
            return r;
    }

    // Input y cálculo
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

    // Dibujado

    ClearBackground(BEIGE);

    DrawRectangle(0, 550, 832, 20, ColorAlpha(WHITE, 0.8));

    Enemigo_DibujarVarios(arreglo_de_enemigos, cantidad_enemigos);

    char buf[200];
    sprintf(
        buf, "Vida: %u",
        vida); // Sin implementación aún, se necesita una pantalla de pérdida.

    if (mostrar_bala)
        DrawTexture(textura_bala, coordenadas_bala.x + colisiones_bala.left,
                    coordenadas_bala.y + colisiones_bala.up, WHITE);
    DrawTexture(textura_pistola, posicion_pistola - 20, 450, WHITE);
    DrawText(buf, 20, 20, 24, BLACK);
    return 1;
}
