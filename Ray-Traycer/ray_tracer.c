#include <stdint.h>
#include "ray_tracer.h"
#include "ray.h"

Color* color_from_ray_hit(Scene* scene, Ray* ray);

Color* traced_value_at_pixel(Ray_tracer* tracer, int x, int y) {
	float xt = x / tracer->width;
	float yt = y / tracer->height;

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
	return NULL;
}