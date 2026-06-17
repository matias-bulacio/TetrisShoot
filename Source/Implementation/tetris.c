#include <tetris.h>
#include <raylib.h>

#define SCREEN_WIDTH 480 //pantalla juego 832 640
#define SCREEN_HEIGHT 600
#define BLOCK_SIZE 30
//hasta aca se crea una ventana de las dimensiones dichas
int meta;
#define FILA 20
#define COLUMN 16
int board[FILA][COLUMN] = {0};
#define PIEZAS_MAX 7
#define FILAS_MAX 4
#define COLUMNAS_MAX 4


int pieza_actual=0;
Color board_color [FILA][COLUMN];
Color color;


int bloque[PIEZAS_MAX][FILAS_MAX][COLUMNAS_MAX]={//7 piezas, 4 filas, 4 columnas
   {{0,0,1,1},
     {0,0,1,1},
     {0,0,0,0},
     {0,0,0,0}},//cuadrado PIEZA 2


    {{0,0,0,0},
     {1,1,1,1},
     {0,0,0,0},
     {0,0,0,0}},//---- PIEZA 1


    {{0,0,1,0},
     {0,1,1,1},
     {0,0,0,0},
     {0,0,0,0}},//T  PIEZA 3
    
    {{1,0,0,0},
     {1,1,1,0},
     {0,0,0,0},
     {0,0,0,0}},// L AL REVES PIEZA 4

    {{0,0,0,1},
     {0,1,1,1},
     {0,0,0,0},
     {0,0,0,0}},//L  PIEZA 5

    {{1,1,0,0},
     {0,1,1,0},
     {0,0,0,0},
     {0,0,0,0}},// Z  pieza 6

    {{0,1,1,0},
     {1,1,0,0},
     {0,0,0,0},
     {0,0,0,0}}// Z AL REVES   PIEZA 7

};

int derecha= 0;
int izquierda=0;
typedef struct //se define las variables para ppoder mover la pieza y se guardan dentro de la estructura pieza
{
    int x;
    int y;
} Piece;



Piece block = {2, 0};//la pieza empieza en la columna 7 y en la fila 0

float timer = 0.0f;
float fallSpeed = 0.5f; // segundos
int primera_vez = 1;
Image bloque_imagen;
Texture2D textura;
int tetris(void)
{
    if(primera_vez) {
        primera_vez = 0;
        bloque_imagen = LoadImage("Resources/Tetris/bloque.png");
        ImageResizeNN(&bloque_imagen, 30, 30);
        textura = LoadTextureFromImage(bloque_imagen);
    }
if (meta==1){
    WaitTime(0.5);
    block.y=2  ;
    block.x=0; 
    pieza_actual=GetRandomValue(0,6); 
    meta=0;
}  
        

if (pieza_actual==0){
    color=RED;
}
 if (pieza_actual==1){
    color=GREEN;
}
 if (pieza_actual==2){
    color=BLUE;
}
 if (pieza_actual==3){
    color=YELLOW;
}
 if (pieza_actual==4){
    color=ORANGE;
}
 if (pieza_actual==5){
    color=PURPLE;
}
 if (pieza_actual==6){
    color=PINK;
}  
    
 //para que se mueva constante sin importar las fps
    float delta = GetFrameTime();
    timer += delta;

//caida automatica
     if (timer >= fallSpeed && meta!=1)
    {
        block.y++;
        timer = 0;
      }
//////////////////////////////////////////////////
    if (meta!=1){// Movimiento horizontal
    if (IsKeyPressed(KEY_LEFT) && izquierda == 0){
        block.x--;}

    if (IsKeyPressed(KEY_RIGHT ) && derecha == 0){
        block.x++;}
    
    if (IsKeyDown(KEY_DOWN)){
        block.y++;}

    if (IsKeyPressed(KEY_UP)){
     ImageRotateCW(&bloque_imagen);  }  
    }   
//////////////////////////////////////////////////
     // Cuadrícula
    for (int x = 0; x < SCREEN_WIDTH; x += BLOCK_SIZE)//creo una variable x y una y para dinbujar lineas
    {
        DrawLine(x, 0, x, SCREEN_HEIGHT, GRAY);}
    

    for (int y = 0; y < SCREEN_HEIGHT; y += BLOCK_SIZE)
    {
        DrawLine(0, y, SCREEN_WIDTH, y, GRAY);}
/////////////////////////////////////////////
    // Limite lateral

     for ( int fila = 0; fila < FILAS_MAX; fila++){//hace que empiece en fila 0 columna 1, columa 2 y asi hasa la 4 donde empieza fila 1

     for ( int columna = 0; columna < COLUMNAS_MAX; columna++){ //tienen el int poorqe son variabes nuevas, un contador detro de filas/clumnas

    if ( bloque[pieza_actual][fila][columna]==1){
        if (block.x + columna>15){//si block.x=13 y la pieza es el rectangulo de 4 entonces 13+3=16 (0,1,2,3) 
            block.x--;

        }
        if (block.x + columna<0){
            block.x++;

        }
    }}}
    
/////////////////////////////////////////////

////////////////////////////////////////////////////////////
    // Piso
    int maxY = 19; //(SCREEN_HEIGHT / BLOCK_SIZE) - 1;
    bool fondo=0;
    
    for ( int fila = 0; fila < FILAS_MAX; fila++){
    for ( int columna = 0; columna < COLUMNAS_MAX; columna++){ 
        
        if ( bloque[pieza_actual][fila][columna]==1){
          if (block.y + fila > maxY ){//si el limite de la pieza supera el del tablero...
               fondo=1;
               
          }}}}
      
    if (fondo==1){//una vez que se acomodo la pieza se guarda la posicion
    block.y--;
        for ( int fila = 0; fila < FILAS_MAX; fila++){
        for ( int columna = 0; columna < COLUMNAS_MAX; columna++){       
            if ( bloque[pieza_actual][fila][columna]==1){
             board[block.y + fila][block.x + columna] = 1; 
             board_color[block.y + fila][block.x + columna]=color;
             DrawTexture(textura, (block.x + columna) * BLOCK_SIZE, (block.y + fila) * BLOCK_SIZE, board_color[fila][columna]);
             
              meta=1;
             }}}}

////////////////////////////////////////////
//colision vertical  CHEQUEAR
int choquev=0;
    for ( int fila = 0; fila < FILAS_MAX; fila++){
    for ( int columna = 0; columna < COLUMNAS_MAX; columna++){ 

    if ( bloque[pieza_actual][fila][columna]==1){
        if (board[block.y + fila + 1][block.x + columna]== 1){//si la pieza se desplaza uno mas choca con algo?
             choquev=1;
             
        }}}}
        
    if (choquev==1){         
    for ( int fila = 0; fila < FILAS_MAX; fila++){
    for ( int columna = 0; columna < COLUMNAS_MAX; columna++){ 
        if ( bloque[pieza_actual][fila][columna]==1){
             board[block.y +  fila][block.x + columna] = 1; 
             board_color[block.y +  fila][block.x + columna]=color;
             DrawTexture(textura, (block.x + columna) * BLOCK_SIZE, (block.y + fila) * BLOCK_SIZE,  board_color[fila][columna]);
         
               }}}
         meta=1;}
////////////////////////////////////////////       
//colision horizontal: revisar que cuando pasa al lado de  una pieza ya no baja porque la detecta
 int choquehd=0;
    for ( int fila = 0; fila < FILAS_MAX; fila++){
    for ( int columna = 0; columna < COLUMNAS_MAX; columna++){  
    if ( bloque[pieza_actual][fila][columna]==1){
        if (board[block.y + fila][block.x + columna + 1]== 1){//si la pieza se desplaza uno a la derecha choca con algo o con el limite?
             choquehd=1;
        }
        
        }}}
    if (choquehd==1){
            derecha=1;       
    }
    if (choquehd==0){
    derecha=0;
    }
    ////
    int choquehi=0;
    for ( int fila = 0; fila < FILAS_MAX; fila++){
    for ( int columna = 0; columna < COLUMNAS_MAX; columna++){  
    if ( bloque[pieza_actual][fila][columna]==1){
        int x=block.x + columna - 1;
        int y=block.y + fila;
         if (board[y][x]== 1){//si la pieza se desplaza uno a la izquierda choca con algo o con el limite?
              choquehi=1;
        }}}}

        if (choquehi==1){
            izquierda=1;       
        }
        if (choquehi==0){
        izquierda=0;
        }
        
////////////////////////////////////////////

/////////////////////////////////////////////
    // Pieza dibujo
    
    for ( int fila = 0; fila < FILAS_MAX; fila++){//hace que empiece en fila 0 columna 1, columa 2 y asi hasa la 4 donde empieza fila 1

    for ( int columna = 0; columna < COLUMNAS_MAX; columna++){ //tienen el int poorqe son variabes nuevas, un contador detro de filas/clumnas

    if ( bloque[pieza_actual][fila][columna]==1){
        DrawTexture(textura, (block.x + columna) * BLOCK_SIZE, (block.y + fila) * BLOCK_SIZE, color);
        // DrawRectangle( (block.x + columna) * BLOCK_SIZE, (block.y + fila) * BLOCK_SIZE, BLOCK_SIZE,BLOCK_SIZE, color);//va a estar ubicado acá, y aca, y va a ser de este tamaño, y de este color
    
    }}}


    // Tablero dibujo
    for (int fila = 0; fila < FILA; fila++)
    {
        for (int columna = 0; columna < COLUMN; columna++)
        {
            if (board[fila][columna] == 1)
            {
                DrawTexture(textura, columna * BLOCK_SIZE, fila * BLOCK_SIZE, board_color[fila][columna]);
                //DrawRectangle(columna * BLOCK_SIZE, fila * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, board_color[fila][columna]);
            }
        }
    }
//////////////////////////////////////////////  

//ROTACION
/* && bloque [pieza_actual][0][0]==2){ //si se presiona la flecha hacia arriba y la pieza es el cuadrado no rota
    pieza_actual=
    int temp[4][4];
    for (int fila = 0; fila < FILAS_MAX; fila++){
        for (int columna = 0; columna < COLUMNAS_MAX; columna++){
            temp[columna][FILAS_MAX - 1 - fila] = bloque[pieza_actual][fila][columna];
        }
    }
    for (int fila = 0; fila < FILAS_MAX; fila++){
        for (int columna = 0; columna < COLUMNAS_MAX; columna++){
            bloque[pieza_actual][fila][columna] = temp[fila][columna];
        }
    }
*/


//////////////////////////////////////////////
    return 0; 
 
}
