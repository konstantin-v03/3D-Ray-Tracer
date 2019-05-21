#include <Windows.h>
#include <stdio.h>
#include "ray_tracer.h"
#include "rgba_image.h"
#include "scene_object.h"

int main() {

	Image_plane image_plane;
	image_plane.top_left =     create_vector3(2, -4, 4);
	image_plane.top_right =    create_vector3(2,  4, 4);
	image_plane.bottom_left =  create_vector3(2, -4, -4);
	image_plane.bottom_right = create_vector3(2,  4, -4);

	Scene scene;
	scene.camera = create_vector3(0, 0, 0);
	scene.image_plane = &image_plane;
	scene.objects = array_list_init();

	float radius = 0.5;
	float radius1 = 0.5;
	float radius2 = 0.5;

	Scene_object* sphere = create_sphere(create_color(1, 0, 0), create_vector3(5, 0, 1), &radius);
	Scene_object* sphere1 = create_sphere(create_color(0, 1, 0), create_vector3(6, 1, 2), &radius1);
	Scene_object* sphere2 = create_sphere(create_color(0, 0, 1), create_vector3(7, 2, 3), &radius2);

	Scene_object* sphere3 = create_sphere(create_color(1, 0, 0), create_vector3(5, 0, -1), &radius);
	Scene_object* sphere4 = create_sphere(create_color(0, 1, 0), create_vector3(6, -1, -2), &radius1);
	Scene_object* sphere5 = create_sphere(create_color(0, 0, 1), create_vector3(7, -2, -3), &radius2);

	array_list_add(scene.objects, sphere);
	array_list_add(scene.objects, sphere1);
	array_list_add(scene.objects, sphere2);
	array_list_add(scene.objects, sphere3);
	array_list_add(scene.objects, sphere4);
	array_list_add(scene.objects, sphere5);

	Ray_tracer ray_tracer;
	ray_tracer.width = 1000;
	ray_tracer.height = 1000;
	ray_tracer.scene = &scene;

	Rgba_image* rgba_image = create_rgba(ray_tracer.width, ray_tracer.height, BMP_TYPE_RGBA);
	Color* color;


	for (int i = 0; i < rgba_image->height; i++) {
		for (int j = 0; j < rgba_image->width; j++) {
			color = traced_value_at_pixel(&ray_tracer, j, i);
			if (color == NULL) {
				rgba_image->RGBA[i][j] = rgba_from_color(0, 0, 0);
			}
			else {
				rgba_image->RGBA[i][j] = rgba_from_color(color->r, color->g, color->b);
			}
		}
	}

	write_rgba("traced.bmp", rgba_image, BMP_TYPE);

	return 0;
}