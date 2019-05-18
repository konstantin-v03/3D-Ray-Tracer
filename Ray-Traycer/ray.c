#include <stdint.h>
#include "ray.h"

vector3* ray_at(ray* ray, float t) {
	return vector_plus(ray->origin, vector_times(ray->dir, t));
}

void free_ray(ray* ray) {
	if (ray == NULL)
		return;
	free(ray->origin);
	free(ray->dir);
	free(ray);
}