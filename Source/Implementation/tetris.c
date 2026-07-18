#include <raylib.h>
#include <tetris.h>

#define SCREEN_WIDTH 630 // pantalla juego 832 640//480 600
#define SCREEN_HEIGHT 630
#define BLOCK_SIZE 30
// hasta aca se crea una ventana de las dimensiones dichas
int meta;
#define FILA 21
#define COLUMN 16
int board[FILA][COLUMN] = {0};
#define PIEZAS_MAX 7
#define FILAS_MAX 4
#define COLUMNAS_MAX 4

int maxY = 20; //(SCREEN_HEIGHT / BLOCK_SIZE) - 1;

#define OPA CLITERAL(Color){230, 41, 55, 180} // Red

int pieza_actual = 0;
Color board_color[FILA][COLUMN];
Color color[7] = {RED, GREEN, BLUE, YELLOW, ORANGE, PURPLE, PINK};
Color color_sig[7] = {RED, GREEN, BLUE, YELLOW, ORANGE, PURPLE, PINK};
Color sig_color;

int bloque[PIEZAS_MAX][FILAS_MAX][COLUMNAS_MAX] = {
    // 7 piezas, 4 filas, 4 columnas
    {{1, 1, 0, 0},
     {1, 1, 0, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}}, // cuadrado PIEZA 2

    {{1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, //---- PIEZA 1

    {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // T  PIEZA 3

    {{1, 0, 0, 0},
     {1, 1, 1, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}}, // L AL REVES PIEZA 4

    {{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // L  PIEZA 5

    {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // Z  pieza 6

    {{0, 1, 1, 0},
     {1, 1, 0, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}} // Z AL REVES   PIEZA 7

};

int DERECHA1[PIEZAS_MAX][FILAS_MAX][COLUMNAS_MAX] = {
    // 7 piezas, 4 filas, 4 columnas
    {{1, 1, 0, 0},
     {1, 1, 0, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}}, // cuadrado PIEZA 2

    {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}}, //---- PIEZA 1

    {{0, 1, 0, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}, // T  PIEZA 3

    {{0, 1, 1, 0},
     {0, 1, 0, 0},
     {0, 1, 0, 0},
     {0, 0, 0, 0}}, // L AL REVES PIEZA 4

    {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}}, // L  PIEZA 5

    {{0, 1, 0, 0}, {1, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}}, // Z  pieza 6

    {{1, 0, 0, 0},
     {1, 1, 0, 0},
     {0, 1, 0, 0},
     {0, 0, 0, 0}} // Z AL REVES   PIEZA 7

};

int DERECHA2[PIEZAS_MAX][FILAS_MAX][COLUMNAS_MAX] = {
    // 7 piezas, 4 filas, 4 columnas
    {{1, 1, 0, 0},
     {1, 1, 0, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}}, // cuadrado PIEZA 2

    {{1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, //---- PIEZA 1

    {{1, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // T  PIEZA 3

    {{1, 1, 1, 0},
     {0, 0, 1, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}}, // L AL REVES PIEZA 4

    {{1, 1, 1, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // L  PIEZA 5

    {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // Z  pieza 6

    {{0, 1, 1, 0},
     {1, 1, 0, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}} // Z AL REVES   PIEZA 7

};

int DERECHA3[PIEZAS_MAX][FILAS_MAX][COLUMNAS_MAX] = {
    // 7 piezas, 4 filas, 4 columnas
    {{1, 1, 0, 0},
     {1, 1, 0, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}}, // cuadrado PIEZA 2

    {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}}, //---- PIEZA 1

    {{0, 1, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}, // T  PIEZA 3

    {{0, 1, 0, 0},
     {0, 1, 0, 0},
     {1, 1, 0, 0},
     {0, 0, 0, 0}}, // L AL REVES PIEZA 4

    {{1, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}, // L  PIEZA 5

    {{0, 1, 0, 0}, {1, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}}, // Z  pieza 6

    {{1, 0, 0, 0},
     {1, 1, 0, 0},
     {0, 1, 0, 0},
     {0, 0, 0, 0}} // Z AL REVES   PIEZA 7

};
int rotacion;
int derecha = 0;
int izquierda = 0;
int gameover = 0;
int choquev;
int choquehd;
int puntos = 0;
int detectar_linea = 0;
int linea_completa = 0;
int linea = 0;

float game_over_time = -1;

int cont = 0;
int tiempo = 0;

int sig_piezas[6] = {0, 0, 0, 0, 0};

typedef struct // se define las variables para ppoder mover la pieza y se
               // guardan dentro de la estructura pieza
{
    int x;
    int y;
} Piece;

Piece block = {7, 0}; // la pieza empieza en la columna 7 y en la fila 0

float timer = 0.0f;
float fallSpeed = 0.5f; // segundos
int primera_vez = 1;
Image bloque_imagen;
Texture2D textura;

bool colisionanV(int rotacion, int num_pieza) {
    int (*arreglo_pieza)[4][4];
    switch (rotacion) {
    case 1:
        arreglo_pieza = &DERECHA1[num_pieza];
        break;
    case 2:
        arreglo_pieza = &DERECHA2[num_pieza];
        break;
    case 3:
        arreglo_pieza = &DERECHA3[num_pieza];
        break;
    case 0:
        arreglo_pieza = &bloque[num_pieza];
        break;
    default:
        return true;
    }
    for (int fila = 0; fila < FILAS_MAX; fila++) {
        for (int columna = 0; columna < COLUMNAS_MAX; columna++) {

            if ((*arreglo_pieza)[fila][columna] == 1) {
                if (board[block.y + fila + 1][block.x + columna] ==
                    1) { // si la pieza se desplaza uno mas choca con algo?
                    return true;
                }
                if (block.y + fila >
                    maxY) { // si el limite de la pieza supera el del tablero...
                    return true;
                }
            }
        }
    }
    return false;
}

int tetris(bool setup) {
    Color colorl = GetColor(0xFFADA2FF);
    if (gameover == 0) {
        DrawRectangle(0, 120, 480, 30, colorl);

        if (primera_vez) {
            primera_vez = 0;
            bloque_imagen = LoadImage("Resources/Tetris/bloque.png");
            ImageResizeNN(&bloque_imagen, 30, 30);
            textura = LoadTextureFromImage(bloque_imagen);
            for (int i = 0; i < 6; i++) {
                sig_piezas[i] = GetRandomValue(0, 6);
            }
        }
        if (meta == 1) {
            WaitTime(0.5);
            timer = 0;
            block.y = 0;
            block.x = 7;
            rotacion = 0;

            for (int fila = 0; fila < FILA; fila++) {
                for (int columna = 0; columna < COLUMN; columna++) {
                    if (board[4][columna] == 1) {

                        gameover = 1;
                    }
                }
            }

            pieza_actual = sig_piezas[1];

            for (int i = 0; i < 5; i++) {
                sig_piezas[i] = sig_piezas[i + 1];
            }
            sig_piezas[5] = GetRandomValue(
                0, 6); // una vez que se desplazaro que se genere u nuevo valor

            meta = 0;
        }

        // para que se mueva constante sin importar las fps
        float delta = GetFrameTime();
        timer += delta;

        // caida automatica
        if (timer >= fallSpeed && meta != 1) {
            block.y++;
            timer = 0;
        }
        //////////////////////////////////////////////////
        if (meta != 1) { // Movimiento horizontal
            if (IsKeyPressed(KEY_LEFT) && izquierda == 0) {
                block.x--;
                izquierda = 1;
            }

            if (IsKeyPressed(KEY_RIGHT) && derecha == 0) {
                block.x++;
                derecha = 1;
            }

            if (IsKeyDown(KEY_DOWN)) {
                if (!colisionanV(rotacion, pieza_actual)) {
                    block.y++;
                }
            }

            if (IsKeyPressed(KEY_UP)) {

                rotacion++;

                if (rotacion == 4) {
                    rotacion = 0;
                }
            }

            if (IsKeyPressed(KEY_SPACE)) {
                while (!colisionanV(rotacion, pieza_actual)) {
                    block.y++;
                }

                // Se pasó una posición
            }
        }

        //////////////////////////////////////////////
        // deteccion de linea completa

        for (int fila = 0; fila < FILA; fila++) {
            linea = 1;
            for (int columna = 0; columna < COLUMN; columna++) {
                if (board[fila][columna] == 0) {

                    linea = 0;
                }
            }
            if (linea == 1) {

                // cada linea vale 100 puntos (sin doubble, triple, etc)
                for (int columna = 0; columna < COLUMN; columna++) {
                    board[fila][columna] = 0;
                    detectar_linea = 1;
                }
            }

            if (detectar_linea == 1) {
                for (int fila2 = fila; fila2 > 0; fila2--) {
                    for (int columna = 0; columna < COLUMN; columna++) {
                        board[fila2][columna] = board[fila2 - 1][columna];

                        board_color[fila2][columna] =
                            board_color[fila2 - 1][columna];
                    }
                }
                linea_completa++; // para puntos
                detectar_linea = 0;
            }
        }
        puntos = linea_completa * 100;
        //////////////////////////////////////////////////

    } // cierre gameover

    //////////////////////////////////////////////////

    //////////////////////////////////////////////////
    // Cuadrícula
    for (int x = 0; x < SCREEN_WIDTH;
         x += BLOCK_SIZE) // creo una variable x y una y para dinbujar lineas
    {
        DrawLine(x, 0, x, SCREEN_HEIGHT, GRAY);
    }

    for (int y = 0; y < SCREEN_HEIGHT; y += BLOCK_SIZE) {
        DrawLine(0, y, SCREEN_WIDTH, y, GRAY);
    }
    /////////////////////////////////////////////
    // Limite lateral

    for (int fila = 0; fila < FILAS_MAX;
         fila++) { // hace que empiece en fila 0 columna 1, columa 2 y asi hasa
                   // la 4 donde empieza fila 1

        for (int columna = 0; columna < COLUMNAS_MAX;
             columna++) { // tienen el int poorqe son variabes nuevas, un
                          // contador detro de filas/clumnas

            switch (rotacion) {
            case 0: {
                if (bloque[pieza_actual][fila][columna] == 1) {
                    if (block.x + columna >
                        15) { // si block.x=13 y la pieza es el rectangulo de 4
                              // entonces 13+3=16 (0,1,2,3)
                        block.x--;
                    }
                    if (block.x + columna < 0) {
                        block.x++;
                    }
                }
                break;
            }

            case 1: {
                if (DERECHA1[pieza_actual][fila][columna] == 1) {
                    if (block.x + columna >
                        15) { // si block.x=13 y la pieza es el rectangulo de 4
                              // entonces 13+3=16 (0,1,2,3)
                        block.x--;
                    }
                    if (block.x + columna < 0) {
                        block.x++;
                    }
                }
                break;
            }

            case 2: {
                if (DERECHA2[pieza_actual][fila][columna] == 1) {
                    if (block.x + columna >
                        15) { // si block.x=13 y la pieza es el rectangulo de 4
                              // entonces 13+3=16 (0,1,2,3)
                        block.x--;
                    }
                    if (block.x + columna < 0) {
                        block.x++;
                    }
                }
                break;
            }

            case 3: {
                if (DERECHA3[pieza_actual][fila][columna] == 1) {
                    if (block.x + columna >
                        15) { // si block.x=13 y la pieza es el rectangulo de 4
                              // entonces 13+3=16 (0,1,2,3)
                        block.x--;
                    }
                    if (block.x + columna < 0) {
                        block.x++;
                    }
                }
                break;
            }
            }
        }
    }

    ////////////////////////////////////////////////////////////
    // Piso
    bool fondo = 0;

    for (int fila = 0; fila < FILAS_MAX; fila++) {
        for (int columna = 0; columna < COLUMNAS_MAX; columna++) {
            switch (rotacion) {
            case 0: {
                if (bloque[pieza_actual][fila][columna] == 1) {
                    if (block.y + fila > maxY) { // si el limite de la pieza
                                                 // supera el del tablero...
                        fondo = 1;
                    }
                }
                break;
            }

            case 1: {
                if (DERECHA1[pieza_actual][fila][columna] == 1) {
                    if (block.y + fila > maxY) { // si el limite de la pieza
                                                 // supera el del tablero...
                        fondo = 1;
                    }
                }
                break;
            }

            case 2: {
                if (DERECHA2[pieza_actual][fila][columna] == 1) {
                    if (block.y + fila > maxY) { // si el limite de la pieza
                                                 // supera el del tablero...
                        fondo = 1;
                    }
                }
                break;
            }

            case 3: {
                if (DERECHA3[pieza_actual][fila][columna] == 1) {
                    if (block.y + fila > maxY) { // si el limite de la pieza
                                                 // supera el del tablero...
                        fondo = 1;
                    }
                }
                break;
            }
            }
        }
    }

    if (fondo == 1) { // una vez que se acomodo la pieza se guarda la posicion
        block.y--;
        for (int fila = 0; fila < FILAS_MAX; fila++) {
            for (int columna = 0; columna < COLUMNAS_MAX; columna++) {
                switch (rotacion) {

                case 0: {
                    if (bloque[pieza_actual][fila][columna] == 1) {
                        board[block.y + fila][block.x + columna] = 1;
                        board_color[block.y + fila][block.x + columna] =
                            color[pieza_actual];
                        DrawTexture(textura, (block.x + columna) * BLOCK_SIZE,
                                    (block.y + fila) * BLOCK_SIZE,
                                    board_color[fila][columna]);

                        meta = 1;
                    }
                    break;
                }

                case 1: {
                    if (DERECHA1[pieza_actual][fila][columna] == 1) {
                        board[block.y + fila][block.x + columna] = 1;
                        board_color[block.y + fila][block.x + columna] =
                            color[pieza_actual];
                        DrawTexture(textura, (block.x + columna) * BLOCK_SIZE,
                                    (block.y + fila) * BLOCK_SIZE,
                                    board_color[fila][columna]);

                        meta = 1;
                    }
                    break;
                }

                case 2: {
                    if (DERECHA2[pieza_actual][fila][columna] == 1) {
                        board[block.y + fila][block.x + columna] = 1;
                        board_color[block.y + fila][block.x + columna] =
                            color[pieza_actual];
                        DrawTexture(textura, (block.x + columna) * BLOCK_SIZE,
                                    (block.y + fila) * BLOCK_SIZE,
                                    board_color[fila][columna]);

                        meta = 1;
                    }
                    break;
                }

                case 3:

                {
                    if (DERECHA3[pieza_actual][fila][columna] == 1) {
                        board[block.y + fila][block.x + columna] = 1;
                        board_color[block.y + fila][block.x + columna] =
                            color[pieza_actual];
                        DrawTexture(textura, (block.x + columna) * BLOCK_SIZE,
                                    (block.y + fila) * BLOCK_SIZE,
                                    board_color[fila][columna]);

                        meta = 1;
                    }
                }
                }
            }
        }
    }

    ////////////////////////////////////////////
    // colision vertical  CHEQUEAR
    choquev = colisionanV(rotacion, pieza_actual);

    if (choquev == 1) {
        for (int fila = 0; fila < FILAS_MAX; fila++) {
            for (int columna = 0; columna < COLUMNAS_MAX; columna++) {

                switch (rotacion) {
                case 0: {
                    if (bloque[pieza_actual][fila][columna] == 1) {
                        board[block.y + fila][block.x + columna] = 1;
                        board_color[block.y + fila][block.x + columna] =
                            color[pieza_actual];
                        DrawTexture(textura, (block.x + columna) * BLOCK_SIZE,
                                    (block.y + fila) * BLOCK_SIZE,
                                    board_color[fila][columna]);
                    }
                    break;
                }

                case 1: {
                    if (DERECHA1[pieza_actual][fila][columna] == 1) {
                        board[block.y + fila][block.x + columna] = 1;
                        board_color[block.y + fila][block.x + columna] =
                            color[pieza_actual];
                        DrawTexture(textura, (block.x + columna) * BLOCK_SIZE,
                                    (block.y + fila) * BLOCK_SIZE,
                                    board_color[fila][columna]);
                    }
                    break;
                }

                case 2: {
                    if (DERECHA2[pieza_actual][fila][columna] == 1) {
                        board[block.y + fila][block.x + columna] = 1;
                        board_color[block.y + fila][block.x + columna] =
                            color[pieza_actual];
                        DrawTexture(textura, (block.x + columna) * BLOCK_SIZE,
                                    (block.y + fila) * BLOCK_SIZE,
                                    board_color[fila][columna]);
                    }
                    break;
                }

                case 3: {
                    if (DERECHA3[pieza_actual][fila][columna] == 1) {
                        board[block.y + fila][block.x + columna] = 1;
                        board_color[block.y + fila][block.x + columna] =
                            color[pieza_actual];
                        DrawTexture(textura, (block.x + columna) * BLOCK_SIZE,
                                    (block.y + fila) * BLOCK_SIZE,
                                    board_color[fila][columna]);
                    }
                    break;
                }
                }
            }
        }

        meta = 1;
    }
    ////////////////////////////////////////////
    // colision horizontal: revisar que cuando pasa al lado de  una pieza ya no
    // baja porque la detecta
    choquehd = 0;
    for (int fila = 0; fila < FILAS_MAX; fila++) {
        for (int columna = 0; columna < COLUMNAS_MAX; columna++) {
            switch (rotacion) {
            case 0: {
                if (bloque[pieza_actual][fila][columna] == 1) {
                    if (board[block.y + fila][block.x + columna + 1] ==
                        1) { // si la pieza se desplaza uno a la derecha choca
                             // con algo o con el limite?
                        choquehd = 1;
                    }
                }
                break;
            }

            case 1: {
                if (DERECHA1[pieza_actual][fila][columna] == 1) {
                    if (board[block.y + fila][block.x + columna + 1] ==
                        1) { // si la pieza se desplaza uno a la derecha choca
                             // con algo o con el limite?
                        choquehd = 1;
                    }
                }
                break;
            }

            case 2: {
                if (DERECHA2[pieza_actual][fila][columna] == 1) {
                    if (board[block.y + fila][block.x + columna + 1] ==
                        1) { // si la pieza se desplaza uno a la derecha choca
                             // con algo o con el limite?
                        choquehd = 1;
                    }
                }
                break;
            }

            case 3: {
                if (DERECHA3[pieza_actual][fila][columna] == 1) {
                    if (board[block.y + fila][block.x + columna + 1] ==
                        1) { // si la pieza se desplaza uno a la derecha choca
                             // con algo o con el limite?
                        choquehd = 1;
                    }
                }
                break;
            }
            }
        }
    }

    if (choquehd == 1) {
        derecha = 1;
    }
    if (choquehd == 0) {
        derecha = 0;
    }
    ////
    int choquehi = 0;
    for (int fila = 0; fila < FILAS_MAX; fila++) {
        for (int columna = 0; columna < COLUMNAS_MAX; columna++) {
            switch (rotacion) {
            case 0: {
                if (bloque[pieza_actual][fila][columna] == 1) {
                    int x = block.x + columna - 1;
                    int y = block.y + fila;
                    if (board[y][x] ==
                        1) { // si la pieza se desplaza uno a la izquierda choca
                             // con algo o con el limite?
                        choquehi = 1;
                    }
                }
                break;
            }

            case 1: {
                if (DERECHA1[pieza_actual][fila][columna] == 1) {
                    int x = block.x + columna - 1;
                    int y = block.y + fila;
                    if (board[y][x] ==
                        1) { // si la pieza se desplaza uno a la izquierda choca
                             // con algo o con el limite?
                        choquehi = 1;
                    }
                }
                break;
            }

            case 2: {
                if (DERECHA2[pieza_actual][fila][columna] == 1) {
                    int x = block.x + columna - 1;
                    int y = block.y + fila;
                    if (board[y][x] ==
                        1) { // si la pieza se desplaza uno a la izquierda choca
                             // con algo o con el limite?
                        choquehi = 1;
                    }
                }
                break;
            }

            case 3: {
                if (DERECHA3[pieza_actual][fila][columna] == 1) {
                    int x = block.x + columna - 1;
                    int y = block.y + fila;
                    if (board[y][x] ==
                        1) { // si la pieza se desplaza uno a la izquierda choca
                             // con algo o con el limite?
                        choquehi = 1;
                    }
                }
                break;
            }
            }
        }
    }

    if (choquehi == 1) {
        izquierda = 1;
    }
    if (choquehi == 0) {
        izquierda = 0;
    }

    ////////////////////////////////////////////

    // Tablero dibujo
    for (int fila = 0; fila < FILA; fila++) {
        for (int columna = 0; columna < COLUMN; columna++) {
            if (board[fila][columna] == 1) {
                DrawTexture(textura, columna * BLOCK_SIZE, fila * BLOCK_SIZE,
                            board_color[fila][columna]);
                // DrawRectangle(columna * BLOCK_SIZE, fila * BLOCK_SIZE,
                // BLOCK_SIZE, BLOCK_SIZE, board_color[fila][columna]);
            }
        }
    }

    //////////////////////////////////////////////

    // ROTACION
    for (int fila = 0; fila < FILAS_MAX;
         fila++) { // hace que empiece en fila 0 columna 1, columa 2 y asi hasa
                   // la 4 donde empieza fila 1

        for (int columna = 0; columna < COLUMNAS_MAX;
             columna++) { // tienen el int poorqe son variabes nuevas, un
                          // contador detro de filas/clumnas

            if (rotacion == 0) {
                if (bloque[pieza_actual][fila][columna] == 1) {

                    DrawTexture(textura, (block.x + columna) * BLOCK_SIZE,
                                (block.y + fila) * BLOCK_SIZE,
                                color[pieza_actual]);
                }
            }

            if (rotacion == 1) {

                if (DERECHA1[pieza_actual][fila][columna] == 1) {

                    DrawTexture(textura, (block.x + columna) * BLOCK_SIZE,
                                (block.y + fila) * BLOCK_SIZE,
                                color[pieza_actual]);
                }
            }

            if (rotacion == 2) {

                if (DERECHA2[pieza_actual][fila][columna] == 1) {
                    DrawTexture(textura, (block.x + columna) * BLOCK_SIZE,
                                (block.y + fila) * BLOCK_SIZE,
                                color[pieza_actual]);
                }
            }

            if (rotacion == 3) {

                if (DERECHA3[pieza_actual][fila][columna] == 1) {

                    DrawTexture(textura, (block.x + columna) * BLOCK_SIZE,
                                (block.y + fila) * BLOCK_SIZE,
                                color[pieza_actual]);
                }
            }
        }
    }
    DrawRectangle(480, 0, 150, 630, WHITE);
    //////////////////////////////////////////////
    for (int fila = 0; fila < 4; fila++) {
        for (int columna = 0; columna < 4; columna++) {

            if (bloque[sig_piezas[1]][fila][columna] == 1) {
                DrawRectangle(510 + columna * BLOCK_SIZE,
                              30 + fila * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE,
                              color_sig[sig_piezas[1]]);
                DrawTexture(textura, 510 + columna * BLOCK_SIZE,
                            30 + fila * BLOCK_SIZE, color_sig[sig_piezas[1]]);
            }

            if (bloque[sig_piezas[2]][fila][columna] == 1) {
                DrawRectangle(510 + columna * BLOCK_SIZE,
                              120 + fila * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE,
                              color_sig[sig_piezas[2]]);
                DrawTexture(textura, 510 + columna * BLOCK_SIZE,
                            120 + fila * BLOCK_SIZE, color_sig[sig_piezas[2]]);
            }

            if (bloque[sig_piezas[3]][fila][columna] == 1) {
                DrawRectangle(510 + columna * BLOCK_SIZE,
                              210 + fila * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE,
                              color_sig[sig_piezas[3]]);
                DrawTexture(textura, 510 + columna * BLOCK_SIZE,
                            210 + fila * BLOCK_SIZE, color_sig[sig_piezas[3]]);
            }

            if (bloque[sig_piezas[4]][fila][columna] == 1) {
                DrawRectangle(510 + columna * BLOCK_SIZE,
                              300 + fila * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE,
                              color_sig[sig_piezas[4]]);
                DrawTexture(textura, 510 + columna * BLOCK_SIZE,
                            300 + fila * BLOCK_SIZE, color_sig[sig_piezas[4]]);
            }

            if (bloque[sig_piezas[5]][fila][columna] == 1) {
                DrawRectangle(510 + columna * BLOCK_SIZE,
                              390 + fila * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE,
                              color_sig[sig_piezas[5]]);
                DrawTexture(textura, 510 + columna * BLOCK_SIZE,
                            390 + fila * BLOCK_SIZE, color_sig[sig_piezas[5]]);
            }
        }
    }

    //////////////////////////////////////////////
    if (gameover == 0) {

        DrawText("PUNTAJE", 510, 470, 20, BLACK);
        DrawText(TextFormat("%d", puntos), 510, 500, 20, BLACK);
        DrawText("TIEMPO", 510, 555, 20, BLACK);

        cont = GetTime();
        if (cont > 120) {
            cont = 120;
        }
        tiempo = 120 - cont;

        if (tiempo > 0 && tiempo <= 120) // tiempo limite de juego
        {
            DrawText(TextFormat("%d s", tiempo), 510, 585, 20, BLACK);
        }
        if (tiempo == 0) {
            DrawText(TextFormat("%d s", 0), 510, 585, 20, BLACK);
            gameover = 1;
        }
    }

    //////////////////////////////////////////////

    if (gameover == 1) {
        DrawRectangle(0, 0, 800, 630, OPA);
        DrawText("Game over", 80, 210, 90, WHITE);
        DrawText("Puntaje:  ", 80, 330, 30, WHITE);
        DrawText(TextFormat("%d", puntos), 220, 330, 30, WHITE);
        DrawText("Tiempo:  ", 80, 400, 30, WHITE);
        if (tiempo == 0) // tiempo limite de juego
        {
            DrawText(TextFormat("%d s", 120), 220, 400, 30, WHITE);
        } else {
            DrawText(TextFormat("%d s", cont), 220, 400, 30, WHITE);
        }
        if (game_over_time == -1) {
            game_over_time = GetTime();
        } else if (GetTime() > game_over_time + 3) {
            return 1;
        }
    }

    return 0;
} // rever limites laterales con el tablero, no se colisionan si estoy tocando
  // el boton de bajar y aarece una nueva
