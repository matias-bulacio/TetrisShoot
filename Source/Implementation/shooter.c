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
#include <shooter_config.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <tetris.h>

PistolData *pistol_data;
BulletData *bullet_data;

Dibujo dib_fondo;
Dibujo *dib_finish_line;
Vector2 coords_finish_line;

Dibujo dib_escondites[5];

ListaEnemigos *lenem;
ListaEscondites *lesc;
ListaEscapes *lexits;

ListaDibujosEnCapas ldib;

int collision_margin;

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

    FILE *file_cfg = Resources_OpenFile("Resources/Shooter/config.ini", "r");
    InitShooterConfig(file_cfg);

    ResetDibujo(&dib_fondo);

    dib_fondo = Resources_LoadCenteredDibujo("Resources/Shooter/pasto.png",
                                             SCREEN_SHOOTER_WIDTH,
                                             SCREEN_SHOOTER_HEIGHT);

    if (!GetFromCfgFinishLine(&dib_finish_line, &coords_finish_line)) {
        TraceLog(LOG_FATAL, "Shooter scene. Bad finish line dibujo.");
        exit(EXIT_FAILURE);
    }

    pistol_data = GetFromCfgPistolData();
    if (!pistol_data) {
        TraceLog(LOG_FATAL, "Shooter scene. Bad pistol data.");
        exit(EXIT_FAILURE);
    }

    bullet_data = GetFromCfgBulletData();
    if (!bullet_data) {
        TraceLog(LOG_FATAL, "Shooter scene. Bad bullet data.");
        exit(EXIT_FAILURE);
    }

    // Setup escondites

    FreeListaEscondites(lesc);
    lesc = GetListaEscondites();
    if (!lesc) {
        TraceLog(LOG_FATAL,
                 "Shooter scene. Bad escondites list from config. Aborting");
        exit(EXIT_FAILURE);
    }

    collision_margin = *GetCollisionMargin();
    for (size_t i = 0; i < lesc->cantidad; i++) {
        Escondite *esc = lesc->arr + i;

        dib_escondites[i] = GetDibujoForTetrisPiece((enum Pieza)sig_piezas[i]);
        esc->dib = &dib_escondites[i];
        int h = esc->dib->textura.height;
        int w = esc->dib->textura.width;

        esc->collision = (CollisionBox){
            .up = -h / 2. + collision_margin,
            .down = h / 2. - collision_margin,
            .left = -w / 2. + collision_margin,
            .right = w / 2. - collision_margin,
        };
    }

    // Setup escapes

    FreeListaEscapes(lexits);
    lexits = GetListaEscapes();
    if (!lexits) {
        TraceLog(LOG_FATAL,
                 "Shooter scene. Bad escapes list from config. Aborting");
        exit(EXIT_FAILURE);
    }

    // Setup enemigos

    FreeListaEnemigos(lenem);
    lenem = GetListaEnemigos();

    for (size_t i = 0; i < lenem->n; i++) {
        Enemigo *e = &lenem->arr[i];
        e->estado = ENEM_STATE_NULL;
        e->le = lesc;
        e->lexits = lexits;
    }
    ldib = NewListaDibujosEnCapas(NUM_ESCONDITES + NUM_ENEMIGOS);
    return 1;
}

int shooter(bool setup) {
    if (setup) {
        int r = setup_shooter();
        if (r != 1)
            return r;
    }

    float delta = GetFrameTime();
    float now = GetTime();

    // Input y cálculo
    int movimiento_pistola = delta * pistol_data->speed *
                             ((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) -
                              (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)));

    pistol_data->coord.x += movimiento_pistola;
    if (bullet_data->show) {
        bullet_data->coord.y -= bullet_data->speed * delta;
    }

    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W) ||
        IsKeyPressed(KEY_SPACE)) {
        bullet_data->show = true;
        bullet_data->coord.x = pistol_data->coord.x;
        bullet_data->coord.y = bullet_data->shooting_height;
    }

    if (bullet_data->coord.y < OFF_SCREEN_TOP)
        bullet_data->show = false;

    if (!bullet_data->show)
        goto sin_bala;

    for (size_t i = 0; i < lenem->n; i++) {
        Enemigo *enem = &lenem->arr[i];
        if (DetectCollision(enem->colisiones, bullet_data->col,
                            enem->coordenadas, bullet_data->coord)) {
            Enemigo_Reset(enem);
            bullet_data->show = false;
            goto sin_bala;
        }
    }

    for (size_t i = 0; i < lesc->cantidad; i++) {
        if (DetectCollision(lesc->arr[i].collision, bullet_data->col,
                            lesc->arr[i].coords, bullet_data->coord)) {
            bullet_data->show = false;
            goto sin_bala;
        }
    }

sin_bala:

    ListaEnemigos_ResetOutOfBounds(lenem, OFF_SCREEN_BOTTOM);
    Update_ListaEnemigos(lenem, now, delta);

    // Dibujado
    ListaDibujosEnCapas_Reset(&ldib);
    for (size_t i = 0; i < lenem->n; i++) {
        Enemigo *e = &lenem->arr[i];
        int layer =
            e->coordenadas.y + e->dib->textura.height + e->dib->offset.y;
        ListaDibujosEnCapas_Insert(&ldib, e->dib, layer, e->coordenadas);
    }
    for (size_t i = 0; i < lesc->cantidad; i++) {
        Escondite *e = &lesc->arr[i];
        int layer = e->coords.y + e->dib->textura.height + e->dib->offset.y;
        ListaDibujosEnCapas_Insert(&ldib, e->dib, layer, e->coords);
    }

    Dibujar(&dib_fondo,
            (Vector2){SCREEN_SHOOTER_WIDTH / 2., SCREEN_SHOOTER_HEIGHT / 2.});

    Dibujar(dib_finish_line, coords_finish_line);

    ListaDibujosEnCapas_Dibujar(&ldib);

    if (bullet_data->show)
        Dibujar(bullet_data->dib, bullet_data->coord);

    Dibujar(pistol_data->dib, pistol_data->coord);

    DrawText(TextFormat("Vida: %u", vida), TEXT_POS_X, TEXT_POS_Y, TEXT_SIZE,
             WHITE);
    return 1;
}
