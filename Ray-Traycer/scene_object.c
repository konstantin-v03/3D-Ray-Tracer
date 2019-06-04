#include "scene_object.h"

Vector3 scene_object_normat_at(Scene_object* scene_object, Vector3* vector) {
	Vector3 to_normalized = vector3_minus(*vector, scene_object->center);

	return vector3_normalized(to_normalized);
}