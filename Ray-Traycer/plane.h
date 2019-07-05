#ifndef PLANE
#define PLANE

#include "scene_object.h"
#include "material.h"

Scene_object* create_plane(Vector3 normal, Vector3 point, Material material);

#endif
