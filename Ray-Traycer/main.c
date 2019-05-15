#include <stdio.h>
#include "rgba_image.h"

int main() {

	rgba_image* image = read_rgba("BMP_IMAGES_PACK/img3.bmp", BMP_TYPE);
	write_rgba("test.png", image, BMP_TYPE);

	return 0;
}