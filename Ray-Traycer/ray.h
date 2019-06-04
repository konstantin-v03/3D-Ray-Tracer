#ifndef RAY
#define RAY

#include "vector3.h"

struct Ray {
	Vector3 origin;
	Vector3 dir;
};

typedef struct Ray Ray;

Vector3 ray_at(Ray* ray, float t);

#endif