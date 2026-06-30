#include <tetris.h>
#include <raylib.h>

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
Color color;

int bloque[PIEZAS_MAX][FILAS_MAX][COLUMNAS_MAX] = {
    // 7 piezas, 4 filas, 4 columnas
    {{1, 1, 0, 0},
     {1, 1, 0, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}}, // cuadrado PIEZA 2

    {{1, 1, 1, 1},
     {0, 0, 0, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}}, //---- PIEZA 1

    {{0, 1, 0, 0},
     {1, 1, 1, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}}, // T  PIEZA 3

    {{1, 0, 0, 0},
     {1, 1, 1, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}}, // L AL REVES PIEZA 4

    {{0, 0, 1, 0},
     {1, 1, 1, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}}, // L  PIEZA 5

    {{1, 1, 0, 0},
     {0, 1, 1, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}}, // Z  pieza 6

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

    {{0, 1, 0, 0},
     {0, 1, 0, 0},
     {0, 1, 0, 0},
     {0, 1, 0, 0}}, //---- PIEZA 1

    {{1, 0, 0, 0},
     {1, 1, 0, 0},
     {1, 0, 0, 0},
     {0, 0, 0, 0}}, // T  PIEZA 3

    {{0, 1, 1, 0},
     {0, 1, 0, 0},
     {0, 1, 0, 0},
     {0, 0, 0, 0}}, // L AL REVES PIEZA 4

    {{0, 1, 0, 0},
     {0, 1, 0, 0},
     {0, 1, 1, 0},
     {0, 0, 0, 0}}, // L  PIEZA 5

    {{0, 1, 0, 0},
     {1, 1, 0, 0},
     {1, 0, 0, 0},
     {0, 0, 0, 0}}, // Z  pieza 6

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

    {{1, 1, 1, 1},
     {0, 0, 0, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}}, //---- PIEZA 1

    {{1, 1, 1, 0},
     {0, 1, 0, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}}, // T  PIEZA 3

    {{1, 1, 1, 0},
     {0, 0, 1, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}}, // L AL REVES PIEZA 4

    {{1, 1, 1, 0},
     {1, 0, 0, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}}, // L  PIEZA 5

    {{1, 1, 0, 0},
     {0, 1, 1, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}}, // Z  pieza 6

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

    {{0, 1, 0, 0},
     {0, 1, 0, 0},
     {0, 1, 0, 0},
     {0, 1, 0, 0}}, //---- PIEZA 1

    {{0, 1, 0, 0},
     {1, 1, 0, 0},
     {0, 1, 0, 0},
     {0, 0, 0, 0}}, // T  PIEZA 3

    {{0, 1, 0, 0},
     {0, 1, 0, 0},
     {1, 1, 0, 0},
     {0, 0, 0, 0}}, // L AL REVES PIEZA 4

    {{1, 1, 0, 0},
     {0, 1, 0, 0},
     {0, 1, 0, 0},
     {0, 0, 0, 0}}, // L  PIEZA 5

    {{0, 1, 0, 0},
     {1, 1, 0, 0},
     {1, 0, 0, 0},
     {0, 0, 0, 0}}, // Z  pieza 6

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

typedef struct // se define las variables para ppoder mover la pieza y se guardan dentro de la estructura pieza
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

bool colisionanV(int rotacion, int num_pieza)
{
    int (*arreglo_pieza)[4][4];
    switch (rotacion)
    {
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
    for (int fila = 0; fila < FILAS_MAX; fila++)
    {
        for (int columna = 0; columna < COLUMNAS_MAX; columna++)
        {

            if ((*arreglo_pieza)[fila][columna] == 1)
            {
                if (board[block.y + fila + 1][block.x + columna] == 1)
                { // si la pieza se desplaza uno mas choca con algo?
                    return true;
                }
                if (block.y + fila > maxY)
                { // si el limite de la pieza supera el del tablero...
                    return true;
                }
            }
        }
    }
    return false;
}

int tetris(void)
{
    Color colorl = GetColor(0xFFADA2FF);
    if (gameover == 0)
    {
        DrawRectangle(0, 120, 480, 30, colorl);
        if (primera_vez)
        {
            primera_vez = 0;
            bloque_imagen = LoadImage("Resources/Tetris/bloque.png");
            ImageResizeNN(&bloque_imagen, 30, 30);
            textura = LoadTextureFromImage(bloque_imagen);
        }
        if (meta == 1)
        {
            WaitTime(0.5);
            timer = 0;
            block.y = 0;
            block.x = 7;
            rotacion = 0;

            for (int fila = 0; fila < FILA; fila++)
            {
                for (int columna = 0; columna < COLUMN; columna++)
                {
                    if (board[4][columna] == 1)
                    {

                        gameover = 1;
                    }
                }
            }

            for (int fila = 0; fila < FILA; fila++)
            {
                for (int columna = 0; columna < COLUMN; columna++)
                {
                    if (board[4][columna] == 0)
                    {

                        pieza_actual = GetRandomValue(0, 6);

                        meta = 0;
                    }
                }
            }
        }

        if (pieza_actual == 0)
        {
            color = RED;
        }
        if (pieza_actual == 1)
        {
            color = GREEN;
        }
        if (pieza_actual == 2)
        {
            color = BLUE;
        }
        if (pieza_actual == 3)
        {
            color = YELLOW;
        }
        if (pieza_actual == 4)
        {
            color = ORANGE;
        }
        if (pieza_actual == 5)
        {
            color = PURPLE;
        }
        if (pieza_actual == 6)
        {
            color = PINK;
        }

        // para que se mueva constante sin importar las fps
        float delta = GetFrameTime();
        timer += delta;

        // caida automatica
        if (timer >= fallSpeed && meta != 1)
        {
            block.y++;
            timer = 0;
        }
        //////////////////////////////////////////////////
        if (meta != 1)
        { // Movimiento horizontal
            if (IsKeyPressed(KEY_LEFT) && izquierda == 0)
            {
                block.x--;
            }

            if (IsKeyPressed(KEY_RIGHT) && derecha == 0)
            {
                block.x++;
            }

            if (IsKeyDown(KEY_DOWN))
            {
                if (!colisionanV(rotacion, pieza_actual))
                {
                    block.y++;
                }
            }
            if (IsKeyPressed(KEY_UP))
            {

                rotacion++;

                if (rotacion == 4)
                {
                    rotacion = 0;
                }
            }

            if (IsKeyPressed(KEY_SPACE))
            {
                while (!colisionanV(rotacion, pieza_actual))
                {
                    block.y++;
                }

                // Se pasó una posición
            }
        }
    }
    //////////////////////////////////////////////////
    // Cuadrícula
    for (int x = 0; x < SCREEN_WIDTH; x += BLOCK_SIZE) // creo una variable x y una y para dinbujar lineas
    {
        DrawLine(x, 0, x, SCREEN_HEIGHT, GRAY);
    }

    for (int y = 0; y < SCREEN_HEIGHT; y += BLOCK_SIZE)
    {
        DrawLine(0, y, SCREEN_WIDTH, y, GRAY);
    }
    /////////////////////////////////////////////
    // Limite lateral

    for (int fila = 0; fila < FILAS_MAX; fila++)
    { // hace que empiece en fila 0 columna 1, columa 2 y asi hasa la 4 donde empieza fila 1

        for (int columna = 0; columna < COLUMNAS_MAX; columna++)
        { // tienen el int poorqe son variabes nuevas, un contador detro de filas/clumnas

            switch (rotacion)
            {
            case 0:
            {
                if (bloque[pieza_actual][fila][columna] == 1)
                {
                    if (block.x + columna > 15)
                    { // si block.x=13 y la pieza es el rectangulo de 4 entonces 13+3=16 (0,1,2,3)
                        block.x--;
                    }
                    if (block.x + columna < 0)
                    {
                        block.x++;
                    }
                }
                break;
            }

            case 1:
            {
                if (DERECHA1[pieza_actual][fila][columna] == 1)
                {
                    if (block.x + columna > 15)
                    { // si block.x=13 y la pieza es el rectangulo de 4 entonces 13+3=16 (0,1,2,3)
                        block.x--;
                    }
                    if (block.x + columna < 0)
                    {
                        block.x++;
                    }
                }
                break;
            }

            case 2:
            {
                if (DERECHA2[pieza_actual][fila][columna] == 1)
                {
                    if (block.x + columna > 15)
                    { // si block.x=13 y la pieza es el rectangulo de 4 entonces 13+3=16 (0,1,2,3)
                        block.x--;
                    }
                    if (block.x + columna < 0)
                    {
                        block.x++;
                    }
                }
                break;
            }

            case 3:
            {
                if (DERECHA3[pieza_actual][fila][columna] == 1)
                {
                    if (block.x + columna > 15)
                    { // si block.x=13 y la pieza es el rectangulo de 4 entonces 13+3=16 (0,1,2,3)
                        block.x--;
                    }
                    if (block.x + columna < 0)
                    {
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

    for (int fila = 0; fila < FILAS_MAX; fila++)
    {
        for (int columna = 0; columna < COLUMNAS_MAX; columna++)
        {
            switch (rotacion)
            {
            case 0:
            {
                if (bloque[pieza_actual][fila][columna] == 1)
                {
                    if (block.y + fila > maxY)
                    { // si el limite de la pieza supera el del tablero...
                        fondo = 1;
                    }
                }
                break;
            }

            case 1:
            {
                if (DERECHA1[pieza_actual][fila][columna] == 1)
                {
                    if (block.y + fila > maxY)
                    { // si el limite de la pieza supera el del tablero...
                        fondo = 1;
                    }
                }
                break;
            }

            case 2:
            {
                if (DERECHA2[pieza_actual][fila][columna] == 1)
                {
                    if (block.y + fila > maxY)
                    { // si el limite de la pieza supera el del tablero...
                        fondo = 1;
                    }
                }
                break;
            }

            case 3:
            {
                if (DERECHA3[pieza_actual][fila][columna] == 1)
                {
                    if (block.y + fila > maxY)
                    { // si el limite de la pieza supera el del tablero...
                        fondo = 1;
                    }
                }
                break;
            }
            }
        }
    }

    if (fondo == 1)
    { // una vez que se acomodo la pieza se guarda la posicion
        block.y--;
        for (int fila = 0; fila < FILAS_MAX; fila++)
        {
            for (int columna = 0; columna < COLUMNAS_MAX; columna++)
            {
                switch (rotacion)
                {

                case 0:
                {
                    if (bloque[pieza_actual][fila][columna] == 1)
                    {
                        board[block.y + fila][block.x + columna] = 1;
                        board_color[block.y + fila][block.x + columna] = color;
                        DrawTexture(textura, (block.x + columna) * BLOCK_SIZE, (block.y + fila) * BLOCK_SIZE, board_color[fila][columna]);

                        meta = 1;
                    }
                    break;
                }

                case 1:
                {
                    if (DERECHA1[pieza_actual][fila][columna] == 1)
                    {
                        board[block.y + fila][block.x + columna] = 1;
                        board_color[block.y + fila][block.x + columna] = color;
                        DrawTexture(textura, (block.x + columna) * BLOCK_SIZE, (block.y + fila) * BLOCK_SIZE, board_color[fila][columna]);

                        meta = 1;
                    }
                    break;
                }

                case 2:
                {
                    if (DERECHA2[pieza_actual][fila][columna] == 1)
                    {
                        board[block.y + fila][block.x + columna] = 1;
                        board_color[block.y + fila][block.x + columna] = color;
                        DrawTexture(textura, (block.x + columna) * BLOCK_SIZE, (block.y + fila) * BLOCK_SIZE, board_color[fila][columna]);

                        meta = 1;
                    }
                    break;
                }

                case 3:

                {
                    if (DERECHA3[pieza_actual][fila][columna] == 1)
                    {
                        board[block.y + fila][block.x + columna] = 1;
                        board_color[block.y + fila][block.x + columna] = color;
                        DrawTexture(textura, (block.x + columna) * BLOCK_SIZE, (block.y + fila) * BLOCK_SIZE, board_color[fila][columna]);

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

    /*for (int fila = 0; fila < FILAS_MAX; fila++)
    {
        for (int columna = 0; columna < COLUMNAS_MAX; columna++)
        {

            if (rotacion == 0)
            {
                if (bloque[pieza_actual][fila][columna] == 1)
                {

                    if (board[block.y + fila + 1][block.x + columna] == 1)
                    { // si la pieza se desplaza uno mas choca con algo?
                        choquev = 1;
                    }
                }
            }

            if (rotacion == 1)
            {
                if (DERECHA1[pieza_actual][fila][columna] == 1)
                {

                    if (board[block.y + fila + 1][block.x + columna] == 1)
                    { // si la pieza se desplaza uno mas choca con algo?
                        choquev = 1;
                    }
                }
            }

            if (rotacion == 2)
            {
                if (DERECHA2[pieza_actual][fila][columna] == 1)
                {

                    if (board[block.y + fila + 1][block.x + columna] == 1)
                    { // si la pieza se desplaza uno mas choca con algo?
                        choquev = 1;
                    }
                }
            }

            if (rotacion == 3)
            {
                if (DERECHA3[pieza_actual][fila][columna] == 1)
                {

                    if (board[block.y + fila + 1][block.x + columna] == 1)
                    { // si la pieza se desplaza uno mas choca con algo?
                        choquev = 1;
                    }
                }
            }
        }
    }*/

    if (choquev == 1)
    {
        for (int fila = 0; fila < FILAS_MAX; fila++)
        {
            for (int columna = 0; columna < COLUMNAS_MAX; columna++)
            {

                switch (rotacion)
                {
                case 0:
                {
                    if (bloque[pieza_actual][fila][columna] == 1)
                    {
                        board[block.y + fila][block.x + columna] = 1;
                        board_color[block.y + fila][block.x + columna] = color;
                        DrawTexture(textura, (block.x + columna) * BLOCK_SIZE, (block.y + fila) * BLOCK_SIZE, board_color[fila][columna]);
                    }
                    break;
                }

                case 1:
                {
                    if (DERECHA1[pieza_actual][fila][columna] == 1)
                    {
                        board[block.y + fila][block.x + columna] = 1;
                        board_color[block.y + fila][block.x + columna] = color;
                        DrawTexture(textura, (block.x + columna) * BLOCK_SIZE, (block.y + fila) * BLOCK_SIZE, board_color[fila][columna]);
                    }
                    break;
                }

                case 2:
                {
                    if (DERECHA2[pieza_actual][fila][columna] == 1)
                    {
                        board[block.y + fila][block.x + columna] = 1;
                        board_color[block.y + fila][block.x + columna] = color;
                        DrawTexture(textura, (block.x + columna) * BLOCK_SIZE, (block.y + fila) * BLOCK_SIZE, board_color[fila][columna]);
                    }
                    break;
                }

                case 3:
                {
                    if (DERECHA3[pieza_actual][fila][columna] == 1)
                    {
                        board[block.y + fila][block.x + columna] = 1;
                        board_color[block.y + fila][block.x + columna] = color;
                        DrawTexture(textura, (block.x + columna) * BLOCK_SIZE, (block.y + fila) * BLOCK_SIZE, board_color[fila][columna]);
                    }
                    break;
                }
                }
            }
        }

        meta = 1;
    }
    ////////////////////////////////////////////
    // colision horizontal: revisar que cuando pasa al lado de  una pieza ya no baja porque la detecta
    choquehd = 0;
    for (int fila = 0; fila < FILAS_MAX; fila++)
    {
        for (int columna = 0; columna < COLUMNAS_MAX; columna++)
        {
            switch (rotacion)
            {
            case 0:
            {
                if (bloque[pieza_actual][fila][columna] == 1)
                {
                    if (board[block.y + fila][block.x + columna + 1] == 1)
                    { // si la pieza se desplaza uno a la derecha choca con algo o con el limite?
                        choquehd = 1;
                    }
                }
                break;
            }

            case 1:
            {
                if (DERECHA1[pieza_actual][fila][columna] == 1)
                {
                    if (board[block.y + fila][block.x + columna + 1] == 1)
                    { // si la pieza se desplaza uno a la derecha choca con algo o con el limite?
                        choquehd = 1;
                    }
                }
                break;
            }

            case 2:
            {
                if (DERECHA2[pieza_actual][fila][columna] == 1)
                {
                    if (board[block.y + fila][block.x + columna + 1] == 1)
                    { // si la pieza se desplaza uno a la derecha choca con algo o con el limite?
                        choquehd = 1;
                    }
                }
                break;
            }

            case 3:
            {
                if (DERECHA3[pieza_actual][fila][columna] == 1)
                {
                    if (board[block.y + fila][block.x + columna + 1] == 1)
                    { // si la pieza se desplaza uno a la derecha choca con algo o con el limite?
                        choquehd = 1;
                    }
                }
                break;
            }
            }
        }
    }

    if (choquehd == 1)
    {
        derecha = 1;
    }
    if (choquehd == 0)
    {
        derecha = 0;
    }
    ////
    int choquehi = 0;
    for (int fila = 0; fila < FILAS_MAX; fila++)
    {
        for (int columna = 0; columna < COLUMNAS_MAX; columna++)
        {
            switch (rotacion)
            {
            case 0:
            {
                if (bloque[pieza_actual][fila][columna] == 1)
                {
                    int x = block.x + columna - 1;
                    int y = block.y + fila;
                    if (board[y][x] == 1)
                    { // si la pieza se desplaza uno a la izquierda choca con algo o con el limite?
                        choquehi = 1;
                    }
                }
                break;
            }

            case 1:
            {
                if (DERECHA1[pieza_actual][fila][columna] == 1)
                {
                    int x = block.x + columna - 1;
                    int y = block.y + fila;
                    if (board[y][x] == 1)
                    { // si la pieza se desplaza uno a la izquierda choca con algo o con el limite?
                        choquehi = 1;
                    }
                }
                break;
            }

            case 2:
            {
                if (DERECHA2[pieza_actual][fila][columna] == 1)
                {
                    int x = block.x + columna - 1;
                    int y = block.y + fila;
                    if (board[y][x] == 1)
                    { // si la pieza se desplaza uno a la izquierda choca con algo o con el limite?
                        choquehi = 1;
                    }
                }
                break;
            }

            case 3:
            {
                if (DERECHA3[pieza_actual][fila][columna] == 1)
                {
                    int x = block.x + columna - 1;
                    int y = block.y + fila;
                    if (board[y][x] == 1)
                    { // si la pieza se desplaza uno a la izquierda choca con algo o con el limite?
                        choquehi = 1;
                    }
                }
                break;
            }
            }
        }
    }

    if (choquehi == 1)
    {
        izquierda = 1;
    }
    if (choquehi == 0)
    {
        izquierda = 0;
    }

    ////////////////////////////////////////////

    // Tablero dibujo
    for (int fila = 0; fila < FILA; fila++)
    {
        for (int columna = 0; columna < COLUMN; columna++)
        {
            if (board[fila][columna] == 1)
            {
                DrawTexture(textura, columna * BLOCK_SIZE, fila * BLOCK_SIZE, board_color[fila][columna]);
                // DrawRectangle(columna * BLOCK_SIZE, fila * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, board_color[fila][columna]);
            }
        }
    }

    //////////////////////////////////////////////

    // ROTACION
    for (int fila = 0; fila < FILAS_MAX; fila++)
    { // hace que empiece en fila 0 columna 1, columa 2 y asi hasa la 4 donde empieza fila 1

        for (int columna = 0; columna < COLUMNAS_MAX; columna++)
        { // tienen el int poorqe son variabes nuevas, un contador detro de filas/clumnas

            if (rotacion == 0)
            {
                if (bloque[pieza_actual][fila][columna] == 1)
                {

                    DrawTexture(textura, (block.x + columna) * BLOCK_SIZE, (block.y + fila) * BLOCK_SIZE, color);
                }
            }

            if (rotacion == 1)
            {

                if (DERECHA1[pieza_actual][fila][columna] == 1)
                {

                    DrawTexture(textura, (block.x + columna) * BLOCK_SIZE, (block.y + fila) * BLOCK_SIZE, color);
                }
            }

            if (rotacion == 2)
            {

                if (DERECHA2[pieza_actual][fila][columna] == 1)
                {
                    DrawTexture(textura, (block.x + columna) * BLOCK_SIZE, (block.y + fila) * BLOCK_SIZE, color);
                }
            }

            if (rotacion == 3)
            {

                if (DERECHA3[pieza_actual][fila][columna] == 1)
                {

                    DrawTexture(textura, (block.x + columna) * BLOCK_SIZE, (block.y + fila) * BLOCK_SIZE, color);
                }
            }
        }
    }
    DrawRectangle(480, 0, 150, 630, WHITE);
    //////////////////////////////////////////////

    //////////////////////////////////////////////
    // fuera del game over
    if (gameover == 1)
    {
        DrawRectangle(0, 0, 800, 630, OPA);
        DrawText("Game over", 80, 210, 90, WHITE);
        DrawText("Puntaje:  ", 80, 280, 50, WHITE);
    }
    return 0;
} // rever limites laterales con el tablero, no se colisionan si estoy tocando el boton de bajar y aarece una nueva
