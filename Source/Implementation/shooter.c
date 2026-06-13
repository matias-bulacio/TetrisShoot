#include <enemigos.h>
#include <puntos.h>
#include <raylib.h>
#include <shooter.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

Enemigo *arreglo_de_enemigos;
Image image;
Texture2D texture;
size_t cantidad_enemigos = 5;

int setup_shooter() {
        if (arreglo_de_enemigos == NULL)
            free(arreglo_de_enemigos);
        cantidad_enemigos = 5;

        arreglo_de_enemigos =
            calloc(cantidad_enemigos, sizeof(*arreglo_de_enemigos));

        if (arreglo_de_enemigos == NULL) {
            return -1; // Error
        }

        for (size_t i = 0; i < cantidad_enemigos; i++) {
            Enemigo *e = &arreglo_de_enemigos[i];
            e->coordenadas.y = 0;
            e->coordenadas.x = 64 + 176 * i;
        }
        if (IsTextureValid(texture)) {
            UnloadTexture(texture);
        }
        image = LoadImage("Resources/Animals/tiger.png");
		ImageResizeNN(&image, 128, 128);
		texture = LoadTextureFromImage(image);
		return 0;
}

int shooter(bool setup) {
    if (setup) { // Seting up
		int r = setup_shooter();
		if (r != 0) return r;
    }
    ClearBackground(BEIGE);

	DrawRectangle(0, 500, 832, 20, ColorAlpha(WHITE, 0.8));
    for (size_t i = 0; i < cantidad_enemigos; i++) {
        Enemigo *e = &arreglo_de_enemigos[i];
        Enemigo_Avanzar(e, 75, GetFrameTime());
        DrawTexture(texture, e->coordenadas.x - 64, e->coordenadas.y - 64, WHITE);
    }

	char buf[200];
	sprintf(buf, "Puntos: %u", puntos);

	DrawText(buf, 20, 20, 24, BLACK);

    return 1;
}
