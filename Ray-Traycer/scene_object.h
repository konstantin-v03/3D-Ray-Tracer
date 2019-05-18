#include "color.h"

struct scene_object_ {
	color* color;
	void* earliest_intersection;
};

typedef struct scene_object_ scene_object;

scene_object* create_sphere(color* color, float r);