#pragma once

#include <raylib.h>
#include <stdbool.h>
typedef struct {
	float left, right, up, down;
} CollisionBox;

bool DetectCollision(CollisionBox a, CollisionBox b, Vector2 posA, Vector2 posB);
