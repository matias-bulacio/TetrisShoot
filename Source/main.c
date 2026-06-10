#include <raylib.h>
#include <stdbool.h>

#ifdef PLATFORM_WEB
#include <emscripten/emscripten.h>
#endif

void setup(void) {
    InitWindow(800, 600, "SnakeGame");

    // InitAudioDevice();

    // Load resources
}

void loop(void) {
    ClearBackground(RAYWHITE);
	DrawCircle(400, 300, 200, RED);
	DrawRectangle(100, 200, 100, 200, GREEN);
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
