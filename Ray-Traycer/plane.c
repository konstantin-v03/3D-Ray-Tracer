#include <stdlib.h>
#include <math.h>
#include "vector3.h"
#include "plane.h"

static float earliest_intersection(Scene_object* plane, Ray ray) {
    Vector3 normal = *((Vector3*)plane->extra_info[0]);

    float temp = vector3_dot(ray.dir, normal);       
    
    if(temp == 0){
        return -1;
    }

	return (vector3_dot(plane->center, normal) - vector3_dot(ray.origin, normal)) / temp;
}

static Vector3 normat_at(Scene_object* plane, Vector3 vector) {
	return vector3_normalized(*((Vector3*)plane->extra_info[0]));
}

static void plane_free(Scene_object* plane){
    if (plane == NULL) {
		return;
	}
    
    free(plane->extra_info[0]);
    free(plane->extra_info);
    free(plane);
}

Scene_object* create_plane(Vector3 normal, Vector3 point, Material material) {
	Scene_object* plane = malloc(sizeof(Scene_object));

	plane->center = point;

	plane->material = material;
	
	plane->extra_info = calloc(1, sizeof(void*));
	plane->extra_info[0] = malloc(sizeof(Vector3));
	*((Vector3*)plane->extra_info[0]) = normal;  

	plane->earliest_intersection = &earliest_intersection;
    plane->normal_at = &normat_at;
    plane->free = &plane_free;

	return plane;
}
