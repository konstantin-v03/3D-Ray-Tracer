#include "scene_object.h"

Vector3 scene_object_normat_at(Scene_object* scene_object, Vector3 vector) {
	return vector3_normalized(vector3_minus(vector, scene_object->center));
}