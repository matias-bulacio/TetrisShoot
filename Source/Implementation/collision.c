#include <collision.h>

bool DetectCollision(CollisionBox a, CollisionBox b, Vector2 posA, Vector2 posB) {
	a.up += posA.y;
	a.down += posA.y;
	a.left += posA.x;
	a.right += posA.x;

	b.up += posB.y;
	b.down += posB.y;
	b.left += posB.x;
	b.right += posB.x;

	if (a.down < b.up) return false;
	if (a.right < b.left) return false;
	if (b.down < a.up) return false;
	if (b.right < a.left) return false;
	
	return true;
}
