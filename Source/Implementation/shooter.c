#include <bloquescaida.h>
#include <collision.h>
#include <enemigos.h>
#include <escape.h>
#include <estadisticas.h>
#include <lista_dibujos.h>
#include <lista_enemigos.h>
#include <lista_escondites.h>
#include <raylib.h>
#include <resources.h>
#include <screen.h>
#include <shooter.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <tetris.h>

Dibujo dib_enemigo;
Dibujo dib_pistola;
Dibujo dib_bala;
Dibujo dib_fondo;

Dibujo dib_escondites[5];

ListaEnemigos lenem;

ListaEscondites lesc;
ListaEscapes lexits;
ListaDibujosEnCapas ldib;

Vector2 coordenadas_bala = {0, OFF_SCREEN_TOP};
bool mostrar_bala = false;
CollisionBox colisiones_bala = (CollisionBox){
    .left = -16,
    .right = 16,
    .down = 18,
    .up = -18,
};

Vector2 coord_pistola = {
    .x = SCREEN_SHOOTER_WIDTH / 2.,
    .y = PISTOL_Y_COORD,
};

Dibujo GetDibujoForTetrisPiece(enum Pieza p) {
    switch (p) {
    case PIEZA_CUADRADO:
        return Resources_LoadCenteredDibujo("Resources/Tetris/cuadrado.png",
                                            TETRIS_PIECES_SCALE * 32,
                                            TETRIS_PIECES_SCALE * 32);
    case PIEZA_L:
        return Resources_LoadCenteredDibujo("Resources/Tetris/L.png",
                                            TETRIS_PIECES_SCALE * 32,
                                            TETRIS_PIECES_SCALE * 48);
    case PIEZA_L_INVERTIDA:
        return Resources_LoadCenteredDibujo("Resources/Tetris/L_invertida.png",
                                            TETRIS_PIECES_SCALE * 48,
                                            TETRIS_PIECES_SCALE * 32);
    case PIEZA_Z_INVERTIDA:
        return Resources_LoadCenteredDibujo("Resources/Tetris/Z_invertida.png",
                                            TETRIS_PIECES_SCALE * 32,
                                            TETRIS_PIECES_SCALE * 48);
    case PIEZA_Z:
        return Resources_LoadCenteredDibujo("Resources/Tetris/Z.png",
                                            TETRIS_PIECES_SCALE * 48,
                                            TETRIS_PIECES_SCALE * 32);
    case PIEZA_LINEA:
        return Resources_LoadCenteredDibujo("Resources/Tetris/linea.png",
                                            TETRIS_PIECES_SCALE * 64,
                                            TETRIS_PIECES_SCALE * 16);
    case PIEZA_T:
        return Resources_LoadCenteredDibujo("Resources/Tetris/T.png",
                                            TETRIS_PIECES_SCALE * 48,
                                            TETRIS_PIECES_SCALE * 32);
    default:
        TraceLog(LOG_FATAL,
                 "%s: Reached impossible state, unknown Tetris piece %d",
                 __func__, (int)p);
        exit(EXIT_FAILURE);
    }
}

// Una función de setup que se llama la primera vez en cada escena
int setup_shooter() {
    SetWindowSize(SCREEN_SHOOTER_WIDTH, SCREEN_SHOOTER_HEIGHT);

    ResetDibujo(&dib_pistola);
    ResetDibujo(&dib_bala);
    ResetDibujo(&dib_enemigo);
    ResetDibujo(&dib_fondo);

    dib_pistola = Resources_LoadCenteredDibujo("Resources/Shooter/pistol.png",
                                               PISTOL_PNG_SIZE);

    dib_bala = Resources_LoadCenteredDibujo("Resources/Shooter/bala.png",
                                            BULLET_PNG_SIZE);
    dib_enemigo = Resources_LoadCenteredDibujo("Resources/Animals/tiger.png",
                                               TIGER_PNG_SIZE);

    dib_fondo = Resources_LoadCenteredDibujo("Resources/Shooter/pasto.png",
                                             SCREEN_SHOOTER_WIDTH,
                                             SCREEN_SHOOTER_HEIGHT);

    // Setup escondites

    FreeListaEscondites(&lesc);
    lesc = NewListaEscondites(NUM_ESCONDITES);
    for (size_t i = 0; i < lesc.cantidad; i++) {
        Escondite *esc = lesc.arr + i;

        dib_escondites[i] = GetDibujoForTetrisPiece((enum Pieza)sig_piezas[i]);
        esc->dib = &dib_escondites[i];
        int h = esc->dib->textura.height;
        int w = esc->dib->textura.width;

        esc->collision = (CollisionBox){
            .up = -h / 2. + COLLISION_MARGIN,
            .down = h / 2. - COLLISION_MARGIN,
            .left = -w / 2. + COLLISION_MARGIN,
            .right = w / 2. - COLLISION_MARGIN,
        };

        esc->zona_escondida = (Vector2){
            .x = 0,
            .y = -h / 2. + COLLISION_MARGIN - 30 * 2 + 15,
        };
        esc->coords = (Vector2){
            .x = 380 + 80 * (i % 2 == 0 ? i : -i),
            .y = 130 + 80 * i,
        };
    }

    // Setup escapes

    FreeListaEscapes(&lexits);
    lexits = NewListaEscapes(NUM_ESCAPES);
    lexits.arr[0].x = FIRST_ESCAPE;
    lexits.arr[1].x = FIRST_ESCAPE + ESCAPE_STEP;
    lexits.arr[2].x = LAST_ESCAPE - 2 * ESCAPE_STEP;
    lexits.arr[3].x = LAST_ESCAPE - ESCAPE_STEP;
    lexits.arr[4].x = LAST_ESCAPE;

    // Setup enemigos

    FreeListaEnemigos(&lenem);
    lenem = NewListaEnemigos(NUM_ENEMIGOS);

    if (lenem.arr == NULL) {
        return -1; // Error
    }

    for (size_t i = 0; i < lenem.n; i++) {
        Enemigo *e = &lenem.arr[i];
        e->coordenadas.y = OFF_SCREEN_TOP;
        e->coordenadas.x = 64 + 176 * i;
        e->colisiones = (CollisionBox){
            .left = -15,
            .right = 15,
            .up = -30,
            .down = 30,
        };
        e->le = &lesc;
        e->dib = &dib_enemigo;
        e->velocidad = GetRandomValue(MIN_VELOCIDAD, MAX_VELOCIDAD);
        e->lexits = &lexits;
    }
    ldib = NewListaDibujosEnCapas(NUM_ESCONDITES + NUM_ENEMIGOS);
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
    int movimiento_pistola = delta * PISTOL_SPEED *
                             ((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) -
                              (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)));

    coord_pistola.x += movimiento_pistola;
    if (mostrar_bala) {
        coordenadas_bala.y -= BULLET_SPEED * delta;
    }

    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W) ||
        IsKeyPressed(KEY_SPACE)) {
        mostrar_bala = true;
        coordenadas_bala.x = coord_pistola.x;
        coordenadas_bala.y = BULLET_Y_COORD;
    }

    if (coordenadas_bala.y < OFF_SCREEN_TOP)
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
                            lesc.arr[i].coords, coordenadas_bala)) {
            mostrar_bala = false;
            goto sin_bala;
        }
    }

sin_bala:

    ListaEnemigos_ResetOutOfBounds(&lenem, OFF_SCREEN_BOTTOM);
    Update_ListaEnemigos(&lenem, now, delta);

    // Dibujado
    ListaDibujosEnCapas_Reset(&ldib);
    for (size_t i = 0; i < lenem.n; i++) {
        Enemigo *e = &lenem.arr[i];
        int layer =
            e->coordenadas.y + e->dib->textura.height + e->dib->offset.y;
        ListaDibujosEnCapas_Insert(&ldib, e->dib, layer, e->coordenadas);
    }
    for (size_t i = 0; i < lesc.cantidad; i++) {
        Escondite *e = &lesc.arr[i];
        int layer = e->coords.y + e->dib->textura.height + e->dib->offset.y;
        ListaDibujosEnCapas_Insert(&ldib, e->dib, layer, e->coords);
    }

    Dibujar(&dib_fondo,
            (Vector2){SCREEN_SHOOTER_WIDTH / 2., SCREEN_SHOOTER_HEIGHT / 2.});

    DrawRectangle(0, FINISH_LINE_COORD, SCREEN_SHOOTER_WIDTH, FINISH_LINE_WIDTH,
                  ColorAlpha(WHITE, FINISH_LINE_OPACITY));

    ListaDibujosEnCapas_Dibujar(&ldib);

    if (mostrar_bala)
        Dibujar(&dib_bala, coordenadas_bala);

    Dibujar(&dib_pistola, coord_pistola);

    DrawText(TextFormat("Vida: %u", vida), TEXT_POS_X, TEXT_POS_Y, TEXT_SIZE,
             WHITE);
    return 1;
}
