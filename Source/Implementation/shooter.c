#include <collision.h>
#include <enemigos.h>
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

Vector2 coordenadas_bala = {0, -100};
bool mostrar_bala = false;
CollisionBox colisiones_bala = (CollisionBox){
    .left = -18,
    .right = 18,
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

    dib_bala = Resources_LoadCenteredDibujo(
        "Resources/Shooter/bala.png",
        colisiones_bala.right - colisiones_bala.left,
        colisiones_bala.down - colisiones_bala.up);
    dib_enemigo =
        Resources_LoadCenteredDibujo("Resources/Animals/tiger.png", 96, 96);

    Image image_escondite = GenImageColor(60, 20, BROWN);
    dib_escondite = LoadDibujoFromCenteredImage(image_escondite);

    // Setup escondites

    // Los primeros 5 escondites son escondites reales para los animales, dentro
    // de la pantalla Los siguientes 5 son falsos, están debajo de la pantalla,
    // y sirve para que los animales lo usen de objetivo, así intentan pasar la
    // línea.
    lesc = NewListaEscondites(10);
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
    }
    for (size_t i = 0; i < 5; i++) {
        Escondite *esc = lesc.arr + i;
        esc->coordinates = (Vector2){
            .x = 380 + 80 * (i % 2 == 0 ? i : -i),
            .y = 120 + 70 * i,
        };
    }
    for (size_t i = 5; i < 10; i++) {
        Escondite *esc = lesc.arr + i;
        esc->coordinates.y = SCREEN_SHOOTER_HEIGHT + 100;
    }
    lesc.arr[5].coordinates.x = 60;
    lesc.arr[6].coordinates.x = 220;
    lesc.arr[7].coordinates.x = 460;
    lesc.arr[8].coordinates.x = 620;
    lesc.arr[9].coordinates.x = 780;

    // Setup enemigos

    if (lenem.arr != NULL)
        free(lenem.arr);
    lenem = NewListaEnemigos(5);

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
        e->velocidad = 75;
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
    int movimiento_pistola = delta * 400 *
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
