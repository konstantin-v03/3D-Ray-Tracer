#ifndef SCENE_OBJECT
#define SCENE_OBJECT

#include "color.h"
#include "ray.h"

typedef struct Scene_object Scene_object;

struct Scene_object {
	Vector3* center;
	Color* color;
	float(*earliest_intersection)(Scene_object* scene_object, Ray* ray);
	void** extra_info;
};

Vector3 scene_object_normat_at(Scene_object* scene_object, Vector3* vector);

#endif