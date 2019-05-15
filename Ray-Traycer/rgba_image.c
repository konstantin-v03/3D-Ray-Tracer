#include "bmp.h"
#include "rgba_image.h"

BMP* generate_bmp_from_rgba(rgba_image* image);
rgba_image* generate_rgba_from_bmp(BMP* bmp);

rgba_image* read_rgba(char* file_name, int file_type) {
	if (file_type == BMP_TYPE) {
		if (file_name == NULL) goto return_null;
		BMP* bmp = read_bmp_image(file_name);
		if (bmp == NULL) goto return_null;
		rgba_image* image = generate_rgba_from_bmp(bmp);
		free_bmp(bmp);
		if (image == NULL) goto return_null;
		return image;
	}

return_null:
	return NULL;
}

int write_rgba(char* file_name, rgba_image* image, int file_type) {
	if (file_type == BMP_TYPE) {
		if (file_name == NULL || image == NULL) goto return_false;
		BMP* bmp = generate_bmp_from_rgba(image);
		if (bmp == NULL) goto return_false;
		int res = write_bmp_image(bmp, file_name);
		free_bmp(bmp);
		return res;
	}

return_false:
	return 1;
}

void free_rgba_image(rgba_image* image) {
	if (image == NULL) {
		return;
	}

	for (int i = 0; i < image->height; i++) {
		free(image->RGBA[i]);
	}
	free(image->RGBA);
	free(image);
}

static BMP* generate_bmp_from_rgba(rgba_image* image) {
	if (image == NULL || !(image->format == BMP_RGB || image->format == BMP_RGBA)) {
		return NULL;
	}

	BMP* bmp = malloc(sizeof(BMP));

	bmp->bmp_file_header = calloc(1, sizeof(BMPFileHeader));;
	bmp->bmp_info_header = calloc(1, sizeof(BMPInfoHeader));
	bmp->bmp_color_header = calloc(1, sizeof(BMPColorHeader));

	if (image->format == BMP_RGB) {
		bmp->bmp_file_header->file_type = BMP_MAGIC_NUMBER;
		bmp->bmp_file_header->offset_data = 54;

		bmp->bmp_info_header->size = 40;
		bmp->bmp_info_header->width = image->width;
		bmp->bmp_info_header->height = image->height;
		bmp->bmp_info_header->bit_count = 24;
		bmp->bmp_info_header->compression = 0;

		int aligment_offset = 0;

		if (image->width % 4 != 0) {
			aligment_offset = 4 - ((image->width * 3) % 4);
		}

		bmp->data_size = image->width * image->height * 3 + (image->height * aligment_offset);
		bmp->data = malloc(bmp->data_size);
		bmp->bmp_file_header->file_size = bmp->bmp_file_header->offset_data + bmp->data_size;

		unsigned char* ptr = (unsigned char*)bmp->data;

		for (int i = 0; i < image->height; i++) {
			for (int j = 0; j < image->width; j++) {
				*ptr = (image->RGBA[i][j] >> 16) & 255;
				ptr++;
				*ptr = (image->RGBA[i][j] >> 8) & 255;
				ptr++;
				*ptr = image->RGBA[i][j] & 255;
				ptr++;
			}
			ptr += aligment_offset;
		}
	}
	else {
		bmp->bmp_file_header->file_type = BMP_MAGIC_NUMBER;
		bmp->bmp_file_header->offset_data = 138;

		bmp->bmp_info_header->size = 124;
		bmp->bmp_info_header->width = image->width;
		bmp->bmp_info_header->height = image->height;
		bmp->bmp_info_header->bit_count = 32;
		bmp->bmp_info_header->compression = 3;

		bmp->bmp_color_header->red_mask = BMP_RED_MASK;
		bmp->bmp_color_header->green_mask = BMP_GREEN_MASK;
		bmp->bmp_color_header->blue_mask = BMP_BLUE_MASK;
		bmp->bmp_color_header->alpha_mask = BMP_ALPHA_MASK;
		bmp->bmp_color_header->color_space_type = 0x73524742;

		bmp->data_size = image->height * image->width * 4;
		bmp->bmp_file_header->file_size = bmp->data_size + bmp->bmp_file_header->offset_data;
		bmp->data = malloc(bmp->data_size);

		for (int i = 0, data_offset = 0; i < image->height; i++) {
			for (int j = 0; j < image->width; j++) {
				bmp->data[data_offset] = image->RGBA[i][j];
				data_offset++;
			}
		}
	}

	return bmp;
}

static rgba_image* generate_rgba_from_bmp(BMP* bmp) {
	if (bmp == NULL || !(bmp->bmp_info_header->bit_count == 32 || bmp->bmp_info_header->bit_count == 24)) {
		return NULL;
	}

	rgba_image* image = malloc(sizeof(rgba_image));

	image->width = bmp->bmp_info_header->width;
	image->height = bmp->bmp_info_header->height;

	if (bmp->bmp_info_header->bit_count == 24) {
		image->format = BMP_RGB;
		image->RGBA = calloc(image->height, sizeof(uint32_t*));

		for (int i = 0; i < image->height; i++) {
			image->RGBA[i] = calloc(image->width, sizeof(uint32_t));
		}

		int aligment_offset = 0;

		if (image->width % 4 != 0) {
			aligment_offset = 4 - ((image->width * 3) % 4);
		}

		unsigned char* ptr = (unsigned char*)bmp->data;
		uint32_t r, g, b;

		for (int i = 0; i < image->height; i++) {
			for (int j = 0; j < image->width; j++) {
				b = (uint32_t)(*ptr) << 16;
				ptr++;
				g = (uint32_t)(*ptr) << 8;
				ptr++;
				r = (uint32_t)(*ptr);
				ptr++;
				image->RGBA[i][j] = r + g + b;
			}
			ptr += aligment_offset;
		}
	}
	else {
		image->format = BMP_RGBA;
		image->RGBA = calloc(image->height, sizeof(uint32_t*));

		for (int i = 0; i < image->height; i++) {
			image->RGBA[i] = calloc(image->width, sizeof(uint32_t));
		}

		for (int i = 0, data_offset = 0; i < image->height; i++) {
			for (int j = 0; j < image->width; j++) {
				image->RGBA[i][j] = bmp->data[data_offset];
				data_offset++;
			}
		}
	}

	return image;
}