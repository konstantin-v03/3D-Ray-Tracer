#ifndef SPHERE
#define SPHERE

#include "scene_object.h"
#include "material.h"

Scene_object* create_sphere(Vector3 center, Material material, float radius);

void free_sphere(Scene_object* sphere);

#endif