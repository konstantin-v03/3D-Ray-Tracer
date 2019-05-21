#include <math.h>
#include "scene_object.h"
#include "array_list.h"

float sphere_earliest_intersection(Scene_object* sphere, Ray* ray);

Scene_object* create_sphere(Color* color, Vector3* center, float* radius) {
	Scene_object* sphere = malloc(sizeof(Scene_object));
	sphere->color = color;
	sphere->extra_info = calloc(2, sizeof(void*));
	sphere->extra_info[0] = (void*)center;
	sphere->extra_info[1] = (void*)radius;
	sphere->earliest_intersection = &sphere_earliest_intersection;

	return sphere;
}

static float sphere_earliest_intersection(Scene_object* sphere, Ray* ray) {
	Vector3* centre = (Vector3*)sphere->extra_info[0];
	float radius = *((float*)sphere->extra_info[1]);

	Vector3* cPrime = vector3_minus(ray->origin, centre);

	float a = vector3_dot(ray->dir, ray->dir);
	float b = 2 * vector3_dot(cPrime, ray->dir);
	float c = vector3_dot(cPrime, cPrime) - radius * radius;

	float d = b * b - 4 * a * c;

	free(cPrime);

	if (d > 0) {
		float sqrt = sqrtf(d);

		float x1 = -b + sqrt / 2 * a;
		float x2 = -b - sqrt / 2 * a;

		if (x1 > x2) {
			return x2;
		}
		else {
			return x1;
		}
	}

	return -1;
}