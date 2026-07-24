#include <collision.h>
#include <enemigos.h>
#include <escape.h>
#include <estadisticas.h>
#include <lista_enemigos.h>
#include <lista_escondites.h>
#include <raylib.h>
#include <resources.h>
#include <screen.h>
#include <shooter.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

Dibujo dib_enemigo;
Dibujo dib_escondite;
Dibujo dib_pistola;
Dibujo dib_bala;

ListaEnemigos lenem;

ListaEscondites lesc;
ListaEscondites escondites_ganadores;
ListaEscapes lexits;

Vector2 coordenadas_bala = {0, -100};
bool mostrar_bala = false;
CollisionBox colisiones_bala = (CollisionBox){
    .left = -16,
    .right = 16,
    .down = 18,
    .up = -18,
};

Vector2 coord_pistola = {
    .x = SCREEN_SHOOTER_WIDTH / 2.,
    .y = SCREEN_SHOOTER_HEIGHT - 80,
};

// Una función de setup que se llama la primera vez en cada escena
int setup_shooter() {
    SetWindowSize(SCREEN_SHOOTER_WIDTH, SCREEN_SHOOTER_HEIGHT);

    ResetDibujo(&dib_pistola);
    ResetDibujo(&dib_bala);
    ResetDibujo(&dib_enemigo);
    ResetDibujo(&dib_escondite);

    dib_pistola =
        Resources_LoadCenteredDibujo("Resources/Shooter/pistol.png", 35, 150);

    dib_bala =
        Resources_LoadCenteredDibujo("Resources/Shooter/bala.png", 40, 45);
    dib_enemigo =
        Resources_LoadCenteredDibujo("Resources/Animals/tiger.png", 96, 96);

    Image image_escondite = GenImageColor(60, 20, BROWN);
    dib_escondite = LoadDibujoFromCenteredImage(image_escondite);

    // Setup escondites

    FreeListaEscondites(&lesc);
    lesc = NewListaEscondites(5);
    for (size_t i = 0; i < lesc.cantidad; i++) {
        Escondite *esc = lesc.arr + i;
        esc->collision = (CollisionBox){
            .up = -5,
            .down = 5,
            .left = -20,
            .right = 20,
        };
        esc->dib = &dib_escondite;
        esc->zona_escondida = (Vector2){
            .x = 0,
            .y = -50,
        };
        esc->coordinates = (Vector2){
            .x = 380 + 80 * (i % 2 == 0 ? i : -i),
            .y = 120 + 70 * i,
        };
    }

    // Setup escapes

    FreeListaEscapes(&lexits);
    lexits = NewListaEscapes(5);
    lexits.arr[0].x = 60;
    lexits.arr[1].x = 220;
    lexits.arr[2].x = 460;
    lexits.arr[3].x = 620;
    lexits.arr[4].x = 780;

    // Setup enemigos

    FreeListaEnemigos(&lenem);
    lenem = NewListaEnemigos(6);

    if (lenem.arr == NULL) {
        return -1; // Error
    }

    for (size_t i = 0; i < lenem.n; i++) {
        Enemigo *e = &lenem.arr[i];
        e->coordenadas.y = -100;
        e->coordenadas.x = 64 + 176 * i;
        e->colisiones = (CollisionBox){
            .left = -15,
            .right = 15,
            .up = -30,
            .down = 30,
        };
        e->le = &lesc;
        e->dib = &dib_enemigo;
        e->velocidad = GetRandomValue(195, 300);
        e->lexits = &lexits;
    }
    return 0;
}

int shooter(bool setup) {
    if (setup) {
        int r = setup_shooter();
        if (r != 0)
            return r;
    }

    float delta = GetFrameTime();
    float now = GetTime();

    // Input y cálculo
    int movimiento_pistola = delta * 600 *
                             ((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) -
                              (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)));

    coord_pistola.x += movimiento_pistola;
    if (mostrar_bala) {
        coordenadas_bala.y -= 1600 * delta;
    }

    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W) ||
        IsKeyPressed(KEY_SPACE)) {
        mostrar_bala = true;
        coordenadas_bala.x = coord_pistola.x;
        coordenadas_bala.y = 520;
    }

    if (coordenadas_bala.y < -50)
        mostrar_bala = false;

    if (!mostrar_bala)
        goto sin_bala;

    for (size_t i = 0; i < lenem.n; i++) {
        Enemigo *enem = &lenem.arr[i];
        if (DetectCollision(enem->colisiones, colisiones_bala,
                            enem->coordenadas, coordenadas_bala)) {
            Enemigo_Reset(enem);
            mostrar_bala = false;
            goto sin_bala;
        }
    }

    for (size_t i = 0; i < lesc.cantidad; i++) {
        if (DetectCollision(lesc.arr[i].collision, colisiones_bala,
                            lesc.arr[i].coordinates, coordenadas_bala)) {
            mostrar_bala = false;
            goto sin_bala;
        }
    }

sin_bala:

    ListaEnemigos_ResetOutOfBounds(&lenem, SCREEN_SHOOTER_HEIGHT + 100);
    Update_ListaEnemigos(&lenem, now, delta);

    // Dibujado

    ClearBackground(BEIGE);

    DrawRectangle(0, 550, 832, 20, ColorAlpha(WHITE, 0.8));

    Dibujar_ListaEnemigos(&lenem);
    Dibujar_ListaEscondites(&lesc);

    if (mostrar_bala)
        Dibujar(&dib_bala, coordenadas_bala);

    Dibujar(&dib_pistola, coord_pistola);

    DrawText(TextFormat("Vida: %u", vida), 20, 20, 24, BLACK);
    return 1;
}
