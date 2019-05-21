#include <stdint.h>
#include "scene_object.h"
#include "ray_tracer.h"
#include "ray.h"

Color* color_from_ray_hit(Scene* scene, Ray* ray);

Color* traced_value_at_pixel(Ray_tracer* tracer, int x, int y) {
	float xt = (float)x / tracer->width;
	float yt = (float)y / tracer->height;

	Vector3* top = vector3_lerp(tracer->scene->image_plane->top_left, tracer->scene->image_plane->top_right, xt);

	Vector3* bottom = vector3_lerp(tracer->scene->image_plane->bottom_left, tracer->scene->image_plane->bottom_right, xt);

	Vector3* point = vector3_lerp(top, bottom , yt);

	free(top);
	free(bottom);

	Ray* ray = malloc(sizeof(Ray));
	ray->origin = point;
	ray->dir = vector3_minus(point, tracer->scene->camera);

	Color* color = malloc(sizeof(Color));

	color = color_from_ray_hit(tracer->scene, ray);

	free(point);
	free(ray);
	
	return color;
}

static Color* color_from_ray_hit(Scene* scene, Ray* ray) {
	if (scene->objects->filled_size <= 0) return NULL;

	Array_list* objects = scene->objects;

	int count_objects = array_list_size(objects);
	float(*earliest_intersection)(Scene_object* scene_object, Ray* ray);
	
	Scene_object* scene_object;
	Color* color = NULL;
	float t;
	float min_t = -1;

	for (int i = 0; i < count_objects; i++) {
		scene_object = (Scene_object*)(array_list_get(objects, i));
		earliest_intersection = scene_object->earliest_intersection;

		t = earliest_intersection(scene_object, ray);

		if(t > 0 && t < min_t || t > 0 && min_t == -1) {
			min_t = t;
			color = scene_object->color;
		}
	}

	if (min_t > 0) {
		return color;
	}

	return NULL;
}