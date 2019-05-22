#include <stdint.h>
#include "ray.h"

Vector3 ray_at(Ray* ray, float t) {
	Vector3 vector = vector3_times(ray->dir, t);

	return vector3_plus(ray->origin, &vector);
}