#include <stdio.h>
#include <stdlib.h>
#include "ray_tracer.h"
#include "rgba_image.h"
#include "sphere.h"
#include "light.h"

char* read_file(char* file_name);
Rgba_image* traced_rgba_image(Scene* scene, int height, int width, int num_bounces);

int main(int argc, char **argv) {
    if(argc != 6){
        goto illegal_args;
        return 0;
    }    
    
    char* scene_json = argv[1];
    char* traced_file_name = argv[2];
    int width = atoi(argv[3]);
    int height = atoi(argv[4]);
    int num_bounces = atoi(argv[5]);

    if(width <= 0 || height <= 0 || num_bounces < 0){
        goto illegal_args;
    }

    char* json_text = read_file(scene_json);

	Scene* scene = scene_from_json(json_text);

    if(scene == NULL){
        printf("Error while reading %s\n", scene_json);
        return 0;
    }

	Rgba_image* rgba_image = traced_rgba_image(scene, width, height, num_bounces);

    scene_free(scene);

	write_rgba(traced_file_name, rgba_image, BMP_TYPE);

	free_rgba_image(rgba_image);

	return 0;
illegal_args:
    printf("Wrong structure of arguments\nMust be:\n1) String(Scene json file name);\n2) String(Traced image file name);\n3) Positive integer(Width of traced image);\n4) Positive integer(Height of traced image);\n5) Positive integer(Num bounces);\n");
    return 0;
}

Rgba_image* traced_rgba_image(Scene* scene, int width, int height, int num_bounces){
    Color** colors = calloc(height, sizeof(Color*));
	//*colors = calloc(height, sizeof(Color*));

	for (int i = 0; i < height; i++) {
		colors[i] = calloc(width, sizeof(Color));
	}

	traced_colors(scene, colors, width, height, num_bounces);

	Rgba_image* rgba_image = create_rgba(width, height, BMP_TYPE_RGBA);
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

    return rgba_image;
}

char* read_file(char* file_name){
   char* buffer = NULL;
   int string_size, read_size;
   FILE* file = fopen(file_name, "r");

   if (file)
   {
       fseek(file, 0, SEEK_END);
       string_size = ftell(file);
       rewind(file);

       buffer = (char*) malloc(sizeof(char) * (string_size + 1));

       read_size = fread(buffer, sizeof(char), string_size, file);

       buffer[string_size] = '\0';

       if (string_size != read_size)
       {
           free(buffer);
           buffer = NULL;
       }

       fclose(file);
    }

    return buffer;
}
