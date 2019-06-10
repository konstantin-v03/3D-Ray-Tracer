#include <Windows.h>
#include <stdio.h>
#include "ray_tracer.h"
#include "rgba_image.h"
#include "sphere.h"
#include "light.h"

static int height = 1000;
static int width = 1000;

int main() {

	Scene scene;
	scene.camera = create_vector3(1, 0, 0);
	scene.image_plane = (Image_plane) { create_vector3(3, -7, 7), create_vector3(3, 7, 7), create_vector3(3, -7, -7), create_vector3(3, 7, -7) };
	scene.kAmbientLight = create_color(0.3, 0.1, 0.21);
	scene.objects = array_list_init();
	scene.lights = array_list_init();

	Scene_object* sphere = create_sphere(create_vector3(5, -1, 1), 
		create_material(create_color(0.2, 0.3, 0.2), create_color(0.6, 0.2, 0.3), create_color(0.7, 0.7, 0.7), create_color(0.9, 0.5, 0.5), 100)
		, 1);

	Scene_object* sphere1 = create_sphere(create_vector3(6, 1, 2), 
		create_material(create_color(0.5, 0.4, 0.1), create_color(0.3, 0.9, 0.1), create_color(0.2, 0.3, 0.7), create_color(0.7, 0.7, 0.7), 25)
	, 1);

	Scene_object* sphere2 = create_sphere(create_vector3(7, 2, 5), 
		create_material(create_color(0.5, 0.3, 0.1), create_color(0.93, 0.52, 0.31), create_color(0.54, 0.2, 0.5), create_color(0.5, 0.5, 0.5), 25)
	, 1);

	array_list_add(scene.objects, sphere);
	array_list_add(scene.objects, sphere1);
	array_list_add(scene.objects, sphere2);

	Light light = create_light(create_vector3(1, 1, 1), create_color(0.7, 0.7, 0.7), create_color(0.8, 0.8, 0.8));

	Light light1 = create_light(create_vector3(7, 7, 1), create_color(0.3, 0.2, 0.1), create_color(0.1, 0.9, 0.3));

	array_list_add(scene.lights, &light);
	array_list_add(scene.lights, &light1);

	Color** colors = calloc(height, sizeof(Color*));
	*colors = calloc(height, sizeof(Color*));

	for (int i = 0; i < height; i++) {
		colors[i] = calloc(width, sizeof(Color));
	}

	traced_scene(&scene, colors, height, width, 3);

	Rgba_image* rgba_image = create_rgba(height, width, BMP_TYPE_RGBA);
	Color color;

	for (int i = 0; i < rgba_image->height; i++) {
		for (int j = 0; j < rgba_image->width; j++) {
			color = colors[i][j];
			if (color.r == COLOR_NULL_VALUE && color.g == COLOR_NULL_VALUE && color.b == COLOR_NULL_VALUE) {
				rgba_image->RGBA[i][j] = rgba_from_color(0, 0, 0);
			}
			else {
				rgba_image->RGBA[i][j] = rgba_from_color(color.r, color.g, color.b);
			}
		}
	}

	for (int i = 0; i < height; i++) {
		free(colors[i]);
	}

	free(colors);

	free_sphere(sphere);
	free_sphere(sphere1);
	free_sphere(sphere2);

	write_rgba("traced.bmp", rgba_image, BMP_TYPE);

	free_rgba_image(rgba_image);

	return 0;
}