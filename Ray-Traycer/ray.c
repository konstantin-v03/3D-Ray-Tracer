#include <stdint.h>
#include "ray.h"

Vector3* ray_at(Ray* ray, float t) {
	Vector3* v1 = vector3_times(ray->dir, t);
	Vector3* v2 = vector3_plus(ray->origin, v1);

	free(v1);
	
	return v2;
}

void free_ray(Ray* ray) {
	if (ray == NULL)
		return;
	free(ray->origin);
	free(ray->dir);
	free(ray);
}