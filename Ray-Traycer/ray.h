#ifndef RAY
#define RAY

#include "vector3.h"

struct Ray {
	Vector3 origin;
	Vector3 dir;
};

typedef struct Ray Ray;

Ray create_ray(Vector3 origin, Vector3 dir);

Vector3 ray_at(Ray ray, float t);

#endif