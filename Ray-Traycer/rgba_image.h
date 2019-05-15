#include <stdint.h>

#define BMP_TYPE 1

struct rgba_image {
	int width;
	int height;
	int format;
	uint32_t** RGBA;
};

typedef struct rgba_image rgba_image;

rgba_image* read_rgba(char* file_name, int type);

int write_rgba(char* file_name, rgba_image* image, int type);

void free_rgba_image(rgba_image* image);