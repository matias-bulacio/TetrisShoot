#include <tetris.h>
#include <raylib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define BLOCK_SIZE 30

typedef struct
{
    int x;
    int y;
} Piece;

Piece block = {5, 0};

float timer = 0.0f;
float fallSpeed = 0.5f; // segundos

int tetris(void)
{
    float delta = GetFrameTime();
    timer += delta;

    // Movimiento horizontal
    if (IsKeyPressed(KEY_LEFT))
        block.x--;

    if (IsKeyPressed(KEY_RIGHT))
        block.x++;

    // Limites laterales
    if (block.x < 0)
        block.x = 0;

    if (block.x > (SCREEN_WIDTH / BLOCK_SIZE) - 1)
        block.x = (SCREEN_WIDTH / BLOCK_SIZE) - 1;

    // Caída rápida
    if (IsKeyDown(KEY_DOWN))
        block.y++;

    // Caída automática
    if (timer >= fallSpeed)
    {
        block.y++;
        timer = 0;
    }

    // Piso
    int maxY = (SCREEN_HEIGHT / BLOCK_SIZE) - 1;
    if (block.y > maxY)
    {
        block.y = 0;
        block.x = 5;
    }

    // Grilla
    for (int x = 0; x < SCREEN_WIDTH; x += BLOCK_SIZE)
    {
        DrawLine(x, 0, x, SCREEN_HEIGHT, DARKGRAY);
    }

    for (int y = 0; y < SCREEN_HEIGHT; y += BLOCK_SIZE)
    {
        DrawLine(0, y, SCREEN_WIDTH, y, DARKGRAY);
    }

    // Pieza
    DrawRectangle(
        block.x * BLOCK_SIZE,
        block.y * BLOCK_SIZE,
        BLOCK_SIZE,
        BLOCK_SIZE,
        RED);

    DrawText("Flechas para mover", 10, 10, 20, WHITE);
    return 0;
}
