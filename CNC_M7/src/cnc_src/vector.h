#ifndef vector_h__
#define vector_h__

#include <asf.h>

class Vector{
public:
	int32_t x;
	int32_t y;
	int32_t z;


	Vector():x(0), y(0), z(0){};
	Vector(int32_t a, int32_t b, int32_t c):x(a), y(b), z(c){};
	Vector(const Vector& v):x(v.x), y(v.y), z(v.z){};
	Vector(Vector* a, Vector* b):x(b->x - a->x), y(b->y - a->y), z(b->z - a->z){};
};

#endif // vector_h__
