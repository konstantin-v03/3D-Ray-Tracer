#ifndef SCENE_OBJECT
#define SCENE_OBJECT

#include "material.h"
#include "color.h"
#include "ray.h"

typedef struct Scene_object Scene_object;

struct Scene_object {
	Vector3 center;
	Material material;
	void** extra_info;
    void(*free)(Scene_object* scene_object);
	float(*earliest_intersection)(Scene_object* scene_object, Ray ray);
    Vector3(*normal_at)(Scene_object* scene_object, Vector3 vector);
};

#endif
