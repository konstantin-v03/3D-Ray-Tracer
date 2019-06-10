#include <stdint.h>
#include "ray.h"

Ray create_ray(Vector3 origin, Vector3 dir) {
	Ray ray;

	ray.dir = dir;
	ray.origin = origin;

	return ray;
}

Vector3 ray_at(Ray ray, float t) {
	return vector3_plus(ray.origin, vector3_times(ray.dir, t));
}