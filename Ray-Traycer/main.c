#include <Windows.h>
#include <stdio.h>
#include "ray_tracer.h"
#include "rgba_image.h"
#include "sphere.h"

int main() {

	Scene scene;
	scene.camera = create_vector3(0, 0, 0);
	scene.image_plane = (Image_plane) { create_vector3(2, -4, 4), create_vector3(2, 4, 4), create_vector3(2, -4, -4), create_vector3(2, 4, -4) };
	scene.objects = array_list_init();

	Scene_object* sphere = create_sphere(create_color(1, 0, 0), create_vector3(5, 0, 1), 0.5);
	Scene_object* sphere1 = create_sphere(create_color(0, 1, 0), create_vector3(6, 1, 2), 0.5);
	Scene_object* sphere2 = create_sphere(create_color(0, 0, 1), create_vector3(7, 2, 3), 0.5);

	array_list_add(scene.objects, sphere);
	array_list_add(scene.objects, sphere1);
	array_list_add(scene.objects, sphere2);

	Ray_tracer ray_tracer;
	ray_tracer.width = 1000;
	ray_tracer.height = 1000;
	ray_tracer.scene = &scene;

	Rgba_image* rgba_image = create_rgba(ray_tracer.width, ray_tracer.height, BMP_TYPE_RGBA);
	Color color;

	for (int i = 0; i < rgba_image->height; i++) {
		for (int j = 0; j < rgba_image->width; j++) {
			color = traced_value_at_pixel(&ray_tracer, j, i);
			if (color.r == COLOR_NULL_VALUE && color.g == COLOR_NULL_VALUE && color.b == COLOR_NULL_VALUE) {
				rgba_image->RGBA[i][j] = rgba_from_color(0, 0, 0);
			}
			else {
				rgba_image->RGBA[i][j] = rgba_from_color(color.r, color.g, color.b);
			}
		}
	}

	free_sphere(sphere);
	free_sphere(sphere1);
	free_sphere(sphere2);

	write_rgba("traced.bmp", rgba_image, BMP_TYPE);

	free_rgba_image(rgba_image);

	return 0;
}