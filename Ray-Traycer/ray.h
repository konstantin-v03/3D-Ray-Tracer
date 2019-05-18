#include "vector3.h"

struct ray {
	vector3* origin;
	vector3* dir;
};

typedef struct ray ray;

vector3* ray_at(ray* ray, float t);

void free_ray(ray* ray);