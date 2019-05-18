#include "color.h"

struct Scene_object {
	Color* color;
	void* earliest_intersection;
};

typedef struct Scene_object Scene_object;

Scene_object* create_sphere(Color* color, float r);