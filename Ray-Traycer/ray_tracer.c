#include <stdint.h>
#include "scene_object.h"
#include "ray_tracer.h"
#include "ray_hit.h"
#include "ray.h"

Color color_from_ray_hit(Scene* scene, Ray* ray);

Color traced_value_at_pixel(Ray_tracer* tracer, int x, int y) {
	float xt = (float)x / tracer->width;
	float yt = (float)y / tracer->height;

	Vector3 v = tracer->scene->camera;

	Vector3 top = vector3_lerp(tracer->scene->image_plane.top_left, tracer->scene->image_plane.top_right, xt);

	Vector3 bottom = vector3_lerp(tracer->scene->image_plane.bottom_left, tracer->scene->image_plane.bottom_right, xt);

	Vector3 point = vector3_lerp(top, bottom , yt);

	Vector3 dir = vector3_minus(point, tracer->scene->camera);

	Ray ray;
	ray.origin = point;
	ray.dir = dir;

    return color_from_ray_hit(tracer->scene, &ray);
}

static Color color_from_ray_hit(Scene* scene, Ray* ray) {
	if (scene->objects->filled_size <= 0) {
		return COLOR_NULL_INSTANCE;
	}

	Array_list* objects = scene->objects;

	int count_objects = array_list_size(objects);
	float(*earliest_intersection)(Scene_object* scene_object, Ray* ray);
	
	Scene_object* scene_object;
	Ray_hit ray_hit; 
	Color color;
	float t;

	ray_hit.t = -1;

	for (int i = 0; i < count_objects; i++) {
		scene_object = (Scene_object*)(array_list_get(objects, i));
		earliest_intersection = scene_object->earliest_intersection;

		t = earliest_intersection(scene_object, ray);

		if(t > 0 && t < ray_hit.t || t > 0 && ray_hit.t == -1) {
			ray_hit.scene_object = scene_object;
			ray_hit.t = t;
		}
	}

	if (ray_hit.t == -1) {
		return COLOR_NULL_INSTANCE;
	}

	Vector3 ray1 = ray_at(ray, ray_hit.t);
	Vector3 normalized = scene_object_normat_at(ray_hit.scene_object, &ray1);

	ray_hit.normalized = normalized;

	return ray_hit.scene_object->color;
}