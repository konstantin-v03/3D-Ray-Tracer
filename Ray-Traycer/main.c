#include <Windows.h>
#include <stdio.h>
#include "ray_tracer.h"
#include "rgba_image.h"
#include "sphere.h"

int main() {

	Vector3 i1, i2, i3, i4, i5;

	i1 = create_vector3(2, -4, 4);
	i2 = create_vector3(2, 4, 4);
	i3 = create_vector3(2, -4, -4);
	i4 = create_vector3(2, 4, -4);
	i5 = create_vector3(0, 0, 0);

	Image_plane image_plane;
	image_plane.top_left = &i1;
	image_plane.top_right = &i2;
	image_plane.bottom_left = &i3;
	image_plane.bottom_right = &i4;

	Scene scene;
	scene.camera = &i5;;
	scene.image_plane = &image_plane;
	scene.objects = array_list_init();

	float radius = 0.5;
	float radius1 = 0.5;
	float radius2 = 0.5;

	Vector3 pos = create_vector3(5, 0, 1);
	Vector3 pos1 = create_vector3(6, 1, 2);
	Vector3 pos2 = create_vector3(7, 2, 3);

	Color c1, c2, c3;
	c1 = create_color(1, 0, 0);
	c2 = create_color(0, 1, 0);
	c3 = create_color(0, 0, 1);

	Scene_object* sphere = create_sphere(&c1, &pos, &radius);
	Scene_object* sphere1 = create_sphere(&c2, &pos1, &radius1);
	Scene_object* sphere2 = create_sphere(&c3, &pos2, &radius2);

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

	write_rgba("traced.bmp", rgba_image, BMP_TYPE);

	return 0;
}