#pragma once

#include <dibujo.h>
#include <screen.h>
#include <stdbool.h>
int shooter(bool setup);

typedef struct PistolData {
    Dibujo *dib;
    int speed;
    Vector2 coord;
} PistolData;

#define BULLET_Y_COORD 520
#define TETRIS_PIECES_SCALE 1.8

#define OFF_SCREEN_TOP -100
#define OFF_SCREEN_LEFT -100
#define OFF_SCREEN_BOTTOM (SCREEN_SHOOTER_HEIGHT + 100)
#define OFF_SCREEN_RIGHT (SCREEN_SHOOTER_WIDTH + 100)

#define BULLET_SPEED 1600

#define NUM_ENEMIGOS 6
#define NUM_ESCONDITES 5

#define BULLET_PNG_X 40
#define BULLET_PNG_Y 45
#define BULLET_PNG_SIZE BULLET_PNG_X, BULLET_PNG_Y

#define TIGER_PNG_X 96
#define TIGER_PNG_Y 96
#define TIGER_PNG_SIZE TIGER_PNG_X, TIGER_PNG_Y

#define TEXT_POS_X 20
#define TEXT_POS_Y 20
#define TEXT_SIZE 24
