#include <stdio.h>
#include <stdlib.h>
#include "ray_tracer.h"
#include "rgba_image.h"
#include "sphere.h"
#include "light.h"

char* read_file(char* filename);

void print(char* t);

static int height = 1000;
static int width = 1000;
static int num_bounces = 3;

int main() {
    char* json_text = read_file("scene.json");

	Scene* scene = scene_from_json(json_text);

    if(scene == NULL){
        return 1;
    }

	Color** colors = calloc(height, sizeof(Color*));
	*colors = calloc(height, sizeof(Color*));

	for (int i = 0; i < height; i++) {
		colors[i] = calloc(width, sizeof(Color));
	}

	traced_scene(scene, colors, height, width, num_bounces);

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

	//free_sphere(sphere);
	//free_sphere(sphere1);
	//free_sphere(sphere2);

    free(scene);

	write_rgba("traced.bmp", rgba_image, BMP_TYPE);

	free_rgba_image(rgba_image);

	return 0;
}

void print(char *t) {
   if (*t == '\0')
      return;
   printf("%c", *t);
   print(++t);
}


char* read_file(char *filename){
   char *buffer = NULL;
   int string_size, read_size;
   FILE *handler = fopen(filename, "r");

   if (handler)
   {
       fseek(handler, 0, SEEK_END);
       string_size = ftell(handler);
       rewind(handler);

       buffer = (char*) malloc(sizeof(char) * (string_size + 1) );

       read_size = fread(buffer, sizeof(char), string_size, handler);

       buffer[string_size] = '\0';

       if (string_size != read_size)
       {
           free(buffer);
           buffer = NULL;
       }

       fclose(handler);
    }

    return buffer;
}
