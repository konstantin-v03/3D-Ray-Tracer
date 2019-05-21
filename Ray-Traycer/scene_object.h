#include "color.h"
#include "ray.h"

typedef struct Scene_object Scene_object;

struct Scene_object {
	Color* color;
	float(*earliest_intersection)(Scene_object* scene_object, Ray* ray);
	void** extra_info;
};

Scene_object* create_sphere(Color* color, Vector3* center, float* radius);