#include <stdint.h>
#include "ray_tracer.h"
#include "ray.h"

color* color_from_ray_hit(scene* scene, ray* ray);

color* traced_value_at_pixel(ray_tracer* tracer, int x, int y) {
	float xt = x / tracer->width;
	float yt = y / tracer->height;

	vector3* top = vector_lerp(tracer->scene->image_plane->top_left, tracer->scene->image_plane->top_right, xt);

	vector3* bottom = vector_lerp(tracer->scene->image_plane->bottom_left, tracer->scene->image_plane->bottom_right, xt);

	vector3* point = vector_lerp(top, bottom , yt);

	free(top);
	free(bottom);

	ray* ray = malloc(sizeof(struct ray));
	ray->origin = point;
	ray->dir = vector_minus(point, tracer->scene->camera);

	color* color = malloc(sizeof(struct color_));

	color = color_from_ray_hit(tracer->scene, ray);

	free(point);
	free(ray);
	
	return color;
}

static color* color_from_ray_hit(scene* scene, ray* ray) {
	return NULL;
}