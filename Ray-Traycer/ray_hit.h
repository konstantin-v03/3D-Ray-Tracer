#include "scene_object.h"

struct Ray_hit{
	Scene_object* scene_object;
	Vector3 normalized;
	float t;
};

typedef struct Ray_hit Ray_hit;
