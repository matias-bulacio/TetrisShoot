#include <raylib.h>
#include <shooter.h>
#include <stdbool.h>
#include <tetris.h>

#define SCREEN_WIDTH 832
#define SCREEN_HEIGHT 640

#ifdef PLATFORM_WEB
#include <emscripten/emscripten.h>
#endif

int escena = 1;
bool ejecutar_setup_de_la_escena = true;

void setup(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "TetrisShoot");

    // InitAudioDevice();

    // Load resources
}

void loop(void) {
    ClearBackground(RAYWHITE);
    switch (escena) {
    case 0:
        escena = tetris(ejecutar_setup_de_la_escena);
		ejecutar_setup_de_la_escena = escena != 0;
        break;
    case 1:
        escena = shooter(ejecutar_setup_de_la_escena);
		ejecutar_setup_de_la_escena = escena != 1;
        break;
    }
}

void final(void) { CloseWindow(); }

int main() {
    setup();
#ifdef PLATFORM_WEB
    emscripten_set_main_loop(loop, 60, true);
#else
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        loop();
        EndDrawing();
    }
#endif
    final();
}
