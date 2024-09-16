#ifndef AABB_H
#define AABB_H

#include <Vector.h>

class AABB {
public:
	AABB(Vector2f mi, Vector2f ma);
	AABB(float x1, float y1, float x2, float y2);

	bool intersects(AABB other);
	void update(Vector2f mi, Vector2f ma);

	Vector2f min;
	Vector2f max;
private:
}

#endif