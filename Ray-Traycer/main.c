#include "ray_tracer.h"
#include "rgba_image.h"

int main() {

	Image_plane image_plane;
	image_plane.top_left = create_vector3(1, 1, 1);
	image_plane.top_right = create_vector3(1, 1, 1);
	image_plane.bottom_left = create_vector3(1, 1, 1);
	image_plane.bottom_right = create_vector3(1, 1, 1);

	Scene scene;
	scene.camera = create_vector3(1, 1, 1);
	scene.image_plane = &image_plane;
	
	Ray_tracer ray_tracer;
	ray_tracer.width = 1920;
	ray_tracer.height = 1080;
	ray_tracer.scene = &scene;

	Rgba_image* rgba_image = create_rgba(ray_tracer.width, ray_tracer.height,BMP_RGBA);
	
	for (int i = 0; i < rgba_image->height; i++) {
		for (int j = 0; j < rgba_image->width; j++) {
			rgba_image->RGBA[i][j] = 1;//traced_value_at_pixel(ray_tracer, 0, 0) to RGBA
		}
	}

	write_rgba("traced.bmp", rgba_image, BMP_TYPE);

	return 0;
}