#include "rgba_image.h"
#include <stdio.h>
#include <stdlib.h>

static BMP* generate_bmp_from_rgba(Rgba_image* rgba_image);
static Rgba_image* generate_rgba_from_bmp(BMP* bmp);

Rgba_image* create_rgba(int width, int height, int format) {
	Rgba_image* rgba_image = malloc(sizeof(Rgba_image));

	rgba_image->width = width;
	rgba_image->height = height;
	rgba_image->format = format;
	rgba_image->RGBA = calloc(rgba_image->height, sizeof(uint32_t*));

	for (int i = 0; i < rgba_image->height; i++) {
		rgba_image->RGBA[i] = calloc(rgba_image->width, sizeof(uint32_t));
	}
    
    return rgba_image;
}

Rgba_image* read_rgba(char* file_name, int file_type) {
	if (file_type == BMP_TYPE) {
		if (file_name == NULL) goto return_null;
		BMP* bmp = read_bmp_image(file_name);
		if (bmp == NULL) goto return_null;
		Rgba_image* rgba_image = generate_rgba_from_bmp(bmp);
		free_bmp(bmp);
		if (rgba_image == NULL) goto return_null;
		return rgba_image;
	}

return_null:
	return NULL;
}

int write_rgba(char* file_name, Rgba_image* rgba_image, int file_type) {
	if (file_type == BMP_TYPE) {
		if (file_name == NULL || rgba_image == NULL) goto return_false;
		BMP* bmp = generate_bmp_from_rgba(rgba_image);
		if (bmp == NULL) goto return_false;
		int res = write_bmp_image(bmp, file_name);
		free_bmp(bmp);
		return res;
	}

return_false:
	return 1;
}

void free_rgba_image(Rgba_image* rgba_image) {
	if (rgba_image == NULL) {
		return;
	}

	for (int i = 0; i < rgba_image->height; i++) {
		free(rgba_image->RGBA[i]);
	}
	free(rgba_image->RGBA);
	free(rgba_image);
}

static BMP* generate_bmp_from_rgba(Rgba_image* rgba_image) {
	if (rgba_image == NULL || !(rgba_image->format == BMP_TYPE_RGB || rgba_image->format == BMP_TYPE_RGBA)) {
		return NULL;
	}

	BMP* bmp = malloc(sizeof(BMP));

	bmp->bmp_file_header = calloc(1, sizeof(BMPFileHeader));;
	bmp->bmp_info_header = calloc(1, sizeof(BMPInfoHeader));
	bmp->bmp_color_header = calloc(1, sizeof(BMPColorHeader));

	if (rgba_image->format == BMP_TYPE_RGB) {
		bmp->bmp_file_header->file_type = BMP_MAGIC_NUMBER;
		bmp->bmp_file_header->offset_data = 54;

		bmp->bmp_info_header->size = 40;
		bmp->bmp_info_header->width = rgba_image->width;
		bmp->bmp_info_header->height = rgba_image->height;
		bmp->bmp_info_header->bit_count = 24;
		bmp->bmp_info_header->compression = 0;

		int aligment_offset = 0;

		if (rgba_image->width % 4 != 0) {
			aligment_offset = 4 - ((rgba_image->width * 3) % 4);
		}

		bmp->data_size = rgba_image->width * rgba_image->height * 3 + (rgba_image->height * aligment_offset);
		bmp->data = malloc(bmp->data_size);
		bmp->bmp_file_header->file_size = bmp->bmp_file_header->offset_data + bmp->data_size;

		unsigned char* ptr = (unsigned char*)bmp->data;

		for (int i = 0; i < rgba_image->height; i++) {
			for (int j = 0; j < rgba_image->width; j++) {
				*ptr = (rgba_image->RGBA[i][j] >> 16) & 255;
				ptr++;
				*ptr = (rgba_image->RGBA[i][j] >> 8) & 255;
				ptr++;
				*ptr = rgba_image->RGBA[i][j] & 255;
				ptr++;
			}
			ptr += aligment_offset;
		}
	}
	else {
		bmp->bmp_file_header->file_type = BMP_MAGIC_NUMBER;
		bmp->bmp_file_header->offset_data = 138;

		bmp->bmp_info_header->size = 124;
		bmp->bmp_info_header->width = rgba_image->width;
		bmp->bmp_info_header->height = rgba_image->height;
		bmp->bmp_info_header->bit_count = 32;
		bmp->bmp_info_header->compression = 3;

		bmp->bmp_color_header->red_mask = BMP_RED_MASK;
		bmp->bmp_color_header->green_mask = BMP_GREEN_MASK;
		bmp->bmp_color_header->blue_mask = BMP_BLUE_MASK;
		bmp->bmp_color_header->alpha_mask = BMP_ALPHA_MASK;
		bmp->bmp_color_header->color_space_type = 0x73524742;

		bmp->data_size = rgba_image->height * rgba_image->width * 4;
		bmp->bmp_file_header->file_size = bmp->data_size + bmp->bmp_file_header->offset_data;
		bmp->data = malloc(bmp->data_size);

		for (int i = 0, data_offset = 0; i < rgba_image->height; i++) {
			for (int j = 0; j < rgba_image->width; j++) {
				bmp->data[data_offset] = rgba_image->RGBA[i][j];
				data_offset++;
			}
		}
	}

	return bmp;
}

static Rgba_image* generate_rgba_from_bmp(BMP* bmp) {
	if (bmp == NULL || !(bmp->bmp_info_header->bit_count == 32 || bmp->bmp_info_header->bit_count == 24)) {
		return NULL;
	}

	Rgba_image* rgba_image = malloc(sizeof(Rgba_image));

	rgba_image->width = bmp->bmp_info_header->width;
	rgba_image->height = bmp->bmp_info_header->height;

	if (bmp->bmp_info_header->bit_count == 24) {
		rgba_image->format = BMP_TYPE_RGB;
		rgba_image->RGBA = calloc(rgba_image->height, sizeof(uint32_t*));

		for (int i = 0; i < rgba_image->height; i++) {
			rgba_image->RGBA[i] = calloc(rgba_image->width, sizeof(uint32_t));
		}

		int aligment_offset = 0;

		if (rgba_image->width % 4 != 0) {
			aligment_offset = 4 - ((rgba_image->width * 3) % 4);
		}

		unsigned char* ptr = (unsigned char*)bmp->data;
		uint32_t r, g, b;

		for (int i = 0; i < rgba_image->height; i++) {
			for (int j = 0; j < rgba_image->width; j++) {
				b = (uint32_t)(*ptr) << 16;
				ptr++;
				g = (uint32_t)(*ptr) << 8;
				ptr++;
				r = (uint32_t)(*ptr);
				ptr++;
				rgba_image->RGBA[i][j] = r + g + b;
			}
			ptr += aligment_offset;
		}
	}
	else {
		rgba_image->format = BMP_TYPE_RGBA;
		rgba_image->RGBA = calloc(rgba_image->height, sizeof(uint32_t*));

		for (int i = 0; i < rgba_image->height; i++) {
			rgba_image->RGBA[i] = calloc(rgba_image->width, sizeof(uint32_t));
		}

		for (int i = 0, data_offset = 0; i < rgba_image->height; i++) {
			for (int j = 0; j < rgba_image->width; j++) {
				rgba_image->RGBA[i][j] = bmp->data[data_offset];
				data_offset++;
			}
		}
	}

	return rgba_image;
}
