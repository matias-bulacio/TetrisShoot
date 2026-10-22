#pragma once

#include <collision.h>
#include <dibujo.h>
#include <screen.h>
#include <stdbool.h>
int shooter(bool setup);

typedef struct PistolData {
    Dibujo *dib;
    int speed;
    Vector2 coord;
} PistolData;

typedef struct BulletData {
    Dibujo *dib;
    int speed;
    Vector2 coord;
    int shooting_height;
    bool show;
    CollisionBox col;
} BulletData;

#define TETRIS_PIECES_SCALE 1.8

#define OFF_SCREEN_TOP -100
#define OFF_SCREEN_LEFT -100
#define OFF_SCREEN_BOTTOM (SCREEN_SHOOTER_HEIGHT + 100)
#define OFF_SCREEN_RIGHT (SCREEN_SHOOTER_WIDTH + 100)

#define NUM_ENEMIGOS 6
#define NUM_ESCONDITES 5

#define TEXT_POS_X 20
#define TEXT_POS_Y 20
#define TEXT_SIZE 24
