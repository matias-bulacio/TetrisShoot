#include <creditos.h>
#include <raylib.h>
#include <resources.h>
#include <bloques_tetris.h>

#define SCREEN_CREDITOS_WIDTH 832
#define SCREEN_CREDITOS_HEIGHT 640

Font fuentealph;

int creditos(bool setup)
{
    ClearBackground(BLACK);
    if (setup)
    {
        fuentealph = LoadFont("Resources/Tipografia/alphbeta.ttf");
    }

    DrawLine(107, 0, 107, 71, WHITE);
    DrawLine(518, 0, 518, 71, WHITE);
    DrawLine(107, 155, 107, 640, WHITE);
    DrawLine(518, 155, 518, 640, WHITE);

    DrawTextEx(fuentealph, "CREDITS", (Vector2){84, 60}, 115, 2, WHITE);
    DrawTextEx(fuentealph, "Tetris Production", (Vector2){190, 205}, 25, 2, WHITE);
    DrawTextEx(fuentealph, "SINER MARIA DEL ROSARIO", (Vector2){128, 235}, 25, 2, WHITE);

    DrawTextEx(fuentealph, "BARZAGHI THIAGO", (Vector2){196, 265}, 25, 2, WHITE);
    DrawTextEx(fuentealph, "Shooter Production", (Vector2){180, 325}, 25, 2, WHITE);
    DrawTextEx(fuentealph, "ADRIAN MATIAS BULACIO", (Vector2){143, 355}, 25, 2, WHITE);

    DrawTextEx(fuentealph, "Music and Art Production", (Vector2){131, 415}, 25, 2, WHITE);
    DrawTextEx(fuentealph, "CHIAPELLO SOTO JULIETA", (Vector2){139, 445}, 25, 2, WHITE);
    DrawTextEx(fuentealph, "KUHN FAUSTINO MIGUEL ", (Vector2){151, 475}, 25, 2, WHITE);
    DrawTextEx(fuentealph, "FERRER JOAQUIN", (Vector2){204, 505}, 25, 2, WHITE);
    DrawTextEx(fuentealph, "FERREYRA TIAGO", (Vector2){204, 535}, 25, 2, WHITE);

    DrawTextEx(fuentealph, "Press ENTER to return to the main menu", (Vector2){115, 600}, 15, 2, GRAY);
    if (IsKeyPressed(KEY_ENTER))
    {
        return 2;
    }
    return 3;
}