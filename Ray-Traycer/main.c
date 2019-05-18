#include "ray_tracer.h"

int main() {

	image_plane* image_plane = malloc(sizeof(image_plane));
	image_plane->top_left = create_vector(1, 1, 1);
	image_plane->top_right = create_vector(1, 1, 1);
	image_plane->bottom_left = create_vector(1, 1, 1);
	image_plane->bottom_right = create_vector(1, 1, 1);

	scene* scene = malloc(sizeof(scene));
	scene->camera = create_vector(1, 1, 1);
	scene->image_plane = image_plane;
	
	ray_tracer* tracer = malloc(sizeof(ray_tracer));
	tracer->width = 1920;
	tracer->height = 1080;
	tracer->scene = scene;

	create_vector(1, 1, 1);

	traced_value_at_pixel(tracer, 0, 0);

	return 0;
}