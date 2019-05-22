#include <math.h>
#include "scene_object.h"
#include "array_list.h"

Scene_object* create_sphere(Color* color, Vector3* center, float* radius);

void free_sphere(Scene_object* sphere);