#include <collision.h>
#include <enemigos.h>
#include <estadisticas.h>
#include <lista_escondites.h>
#include <raylib.h>
#include <resources.h>
#include <shooter.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

Dibujo dib_enemigo;
Dibujo dib_escondite;
Dibujo dib_pistola;
Dibujo dib_bala;

Enemigo *arreglo_de_enemigos;
size_t cantidad_enemigos = 5;

ListaEscondites le;
ListaEscondites escondites_ganadores;

Vector2 coordenadas_bala = {0, -100};
bool mostrar_bala = false;
CollisionBox colisiones_bala = (CollisionBox){
    .left = -18,
    .right = 18,
    .down = 18,
    .up = -18,
};

// SCREEN_WIDTH/2
Vector2 coord_pistola = {
    .x = 416,
    .y = 550,
};

// Una función de setup que se llama la primera vez en cada escena
int setup_shooter() {
    if (IsTextureValid(dib_pistola.textura)) {
        UnloadTexture(dib_pistola.textura);
    }
    Image image_pistola = Resources_LoadImage("Resources/Shooter/pistol.png");
    ImageResizeNN(&image_pistola, 35, 150);
    dib_pistola = LoadDibujoFromCenteredImage(image_pistola);

    if (IsTextureValid(dib_bala.textura)) {
        UnloadTexture(dib_bala.textura);
    }
    Image image_bala = Resources_LoadImage("Resources/Shooter/bala.png");
    ImageResizeNN(&image_bala, colisiones_bala.right - colisiones_bala.left,
                  colisiones_bala.down - colisiones_bala.up);
    dib_bala = LoadDibujoFromCenteredImage(image_bala);

    if (IsTextureValid(dib_enemigo.textura)) {
        UnloadTexture(dib_enemigo.textura);
    }

    Image image_enemigo = Resources_LoadImage("Resources/Animals/tiger.png");
    ImageResizeNN(&image_enemigo, 96, 96);
    dib_enemigo = LoadDibujoFromCenteredImage(image_enemigo);

    if (arreglo_de_enemigos == NULL)
        free(arreglo_de_enemigos);
    cantidad_enemigos = 5;

    arreglo_de_enemigos =
        calloc(cantidad_enemigos, sizeof(*arreglo_de_enemigos));

    if (arreglo_de_enemigos == NULL) {
        return -1; // Error
    }

    Image image_escondite = GenImageColor(60, 20, BROWN);
    dib_escondite = LoadDibujoFromCenteredImage(image_escondite);

    le = NewListaEscondites(10);
    for (size_t i = 0; i < 5; i++) {
		Escondite *esc = le.arr + i;
        esc->collision = (CollisionBox){
            .up = -5,
            .down = 5,
            .left = -20,
            .right = 20,
        };
        esc->coordinates = (Vector2){
            .y = 120 + 70 * i,
            .x = 380 + 80 * (i % 2 == 0 ? i : -i),
        };
        esc->dib = &dib_escondite;
		esc->zona_escondida = (Vector2) {
			.x = 0,
			.y = -50,
		};
    }
	le.arr[5].coordinates.x =  60;
	le.arr[6].coordinates.x = 220;
	le.arr[7].coordinates.x = 460;
	le.arr[8].coordinates.x = 620;
	le.arr[9].coordinates.x = 780;
    for (size_t i = 5; i < 10; i++) {
		Escondite *esc = le.arr + i;
        esc->collision = (CollisionBox){
            .up = -5,
            .down = 5,
            .left = -20,
            .right = 20,
        };
        esc->coordinates.y = 640 + 100;
        esc->dib = &dib_escondite;
		esc->zona_escondida = (Vector2) {
			.x = 0,
			.y = -50,
		};
    }

    // TODO: Mover estos números mágicos a una configuración
    for (size_t i = 0; i < cantidad_enemigos; i++) {
        Enemigo *e = &arreglo_de_enemigos[i];
        e->coordenadas.y = -100;
        e->coordenadas.x = 64 + 176 * i;
        e->colisiones = (CollisionBox){
            .left = -15,
            .right = 15,
            .up = -30,
            .down = 30,
        };
		e->le = &le;
        e->dib = &dib_enemigo;
		e->velocidad = 75;
    }
    return 0;
}

int shooter(bool setup) {
    float delta = GetFrameTime();
    float now = GetTime();
    if (setup) {
        int r = setup_shooter();
        if (r != 0)
            return r;
    }

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

    for (size_t i = 0; i < cantidad_enemigos; i++) {
        Enemigo *e = &arreglo_de_enemigos[i];
        Enemigo_Update(e, now, delta);
        if (mostrar_bala) {
            if (DetectCollision(e->colisiones, colisiones_bala, e->coordenadas,
                                coordenadas_bala)) {
                mostrar_bala = false;
                e->coordenadas.y = 2000;
				e->esc->ocupado = false;
            }
        }
		if (e->coordenadas.y > 640 + 100) {
			e->estado = ENEM_STATE_INACTIVO;
			e->coordenadas.y = -100;
		}
    }

    for (size_t i = 0; i < le.cantidad; i++) {
        if (mostrar_bala &&
            DetectCollision(le.arr[i].collision, colisiones_bala,
                            le.arr[i].coordinates, coordenadas_bala)) {
            mostrar_bala = false;
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
        Dibujar(&dib_bala, coordenadas_bala);
    Dibujar(&dib_pistola, coord_pistola);
    for (size_t i = 0; i < le.cantidad; i++) {
        Dibujar(le.arr[i].dib, le.arr[i].coordinates);
    }
    DrawText(buf, 20, 20, 24, BLACK);
    return 1;
}
