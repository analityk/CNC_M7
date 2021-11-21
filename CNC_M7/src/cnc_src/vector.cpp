#include <vector.h>
#include <math.h>


float Vector::Length(Vector* a, Vector* b)
{
	float x = b->x - a->x;
	float y = b->y - a->y;
	float z = b->z - a->z;

	float xx = pow(x, 2);
	float yy = pow(y, 2);
	float zz = pow(z, 2);

	return (float)sqrt(xx + yy + zz);
};
