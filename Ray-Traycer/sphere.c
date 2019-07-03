#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "sphere.h"

float sphere_earliest_intersection(Scene_object* sphere, Ray ray) {
	float radius = *((float*)(sphere->extra_info[0]));

	Vector3 cPrime = vector3_minus(ray.origin, sphere->center);

	float a = vector3_dot(ray.dir, ray.dir);
	float b = 2 * vector3_dot(cPrime, ray.dir);
	float c = vector3_dot(cPrime, cPrime) - radius * radius;

	float d = b * b - 4 * a * c;

	if (d > 0) {
		float min;

		float sqrt = sqrtf(d);

		float x1 = (-b + sqrt) / (2 * a);
		float x2 = (-b - sqrt) / (2 * a);

		if (x1 > x2) {
			min = x2;
		}
		else {
			min = x1;
		}

		if (min > 0) {
			return min;
		}
	}

	return -1;
}

Scene_object* create_sphere(Vector3 center, Material material, float radius) {
	Scene_object* sphere = malloc(sizeof(Scene_object));

	sphere->center = center;

    /*
    printf("%f %f %f\n", material.kAmbient.r, material.kAmbient.g, material.kAmbient.b);
    printf("%f %f %f\n", material.kDiffuse.r, material.kDiffuse.g, material.kDiffuse.b);
    printf("%f %f %f\n", material.kSpecular.r, material.kSpecular.g, material.kSpecular.b);
    printf("%i\n----\n", material.alpha);
    */

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
