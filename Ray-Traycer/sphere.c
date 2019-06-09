#include <math.h>
#include "sphere.h"
#include <stdio.h>

float sphere_earliest_intersection(Scene_object* sphere, Ray* ray);

Scene_object* create_sphere(Vector3 center, Material material, float radius) {
	Scene_object* sphere = malloc(sizeof(Scene_object));

	sphere->center = center;

	sphere->material.kAmbient = material.kAmbient;
	sphere->material.kDiffuse = material.kDiffuse;
	sphere->material.kSpecular = material.kSpecular;
	sphere->material.kReflection = material.kReflection;
	sphere->material.alpha = material.alpha;
	
	sphere->extra_info = calloc(1, sizeof(void*));
	sphere->extra_info[0] = malloc(sizeof(float));
	*((float*)sphere->extra_info[0]) = radius;
	sphere->earliest_intersection = &sphere_earliest_intersection;

	return sphere;
}

void free_sphere(Scene_object* sphere) {
	if (sphere == NULL) {
		return;
	}

	free(sphere->extra_info[0]);
	free(sphere->extra_info);
	free(sphere);
}

static float sphere_earliest_intersection(Scene_object* sphere, Ray* ray) {
	float radius = *((float*)(sphere->extra_info[0]));

	Vector3 cPrime = vector3_minus(ray->origin, sphere->center);

	float a = vector3_dot(ray->dir, ray->dir);
	float b = 2 * vector3_dot(cPrime, ray->dir);
	float c = vector3_dot(cPrime, cPrime) - radius * radius;

	float d = b * b - 4 * a * c;

	if (d > 0) {
		float sqrt = sqrtf(d);

		float x1 = (-b + sqrt) / (2 * a);
		float x2 = (-b - sqrt) / (2 * a);

		if (x1 < 0 && x2 >= 0) {
			return x2;
		}
		else if (x2 < 0 && x1 >= 0) {
			return x1;
		}
		else if(x1 < 0 && x2 < 0){
			return -1;
		}

		if (x1 > x2) {
			return x2;
		}
		else {
			return x1;
		}
	}

	return -1;
}