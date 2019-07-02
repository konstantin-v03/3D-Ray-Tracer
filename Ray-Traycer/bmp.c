#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

static int check_rgba_color_header(BMPColorHeader* bmp_color_header);

BMP* read_bmp_image(char* file_name) {
	if (file_name == NULL) {
		return NULL;
	}

	FILE* file;

	if ((file = fopen(file_name, "rb")) == NULL) {
		return NULL;
	}

	BMP* bmp = malloc(sizeof(BMP));

	bmp->bmp_file_header = malloc(sizeof(BMPFileHeader));
	bmp->bmp_info_header = malloc(sizeof(BMPInfoHeader));
	bmp->bmp_color_header = malloc(sizeof(BMPColorHeader));

	fread(bmp->bmp_file_header, sizeof(BMPFileHeader), 1, file);

	if (bmp->bmp_file_header->file_type != BMP_MAGIC_NUMBER) {
		return NULL;
	}

	fread(bmp->bmp_info_header, sizeof(BMPInfoHeader), 1, file);

	if (bmp->bmp_info_header->bit_count == 32 && bmp->bmp_info_header->compression == 3) {
		if(bmp->bmp_info_header->size >= (sizeof(BMPInfoHeader) + sizeof(BMPColorHeader))) {
			fread(bmp->bmp_color_header, sizeof(BMPColorHeader), 1, file);
			if (check_rgba_color_header(bmp->bmp_color_header) != 0) {
				return NULL;
			}
		}
		else {
			return NULL;
		}
	}
	else if (!(bmp->bmp_info_header->bit_count == 24 && bmp->bmp_info_header->compression == 0)) {
		return NULL;
	}

	if (bmp->bmp_info_header->height < 0) {
		return NULL;
	}

	fseek(file, bmp->bmp_file_header->offset_data, SEEK_SET);

	bmp->data_size = bmp->bmp_file_header->file_size - bmp->bmp_file_header->offset_data;

	bmp->data = malloc(bmp->data_size);

	fread(bmp->data, bmp->data_size, 1, file);

	fclose(file);

	return bmp;
}

int write_bmp_image(BMP* bmp, char* file_name) {
	if (bmp == NULL || file_name == NULL) {
		return 1;
	}

	FILE* file;

	if ((file = fopen(file_name, "wb")) == NULL) {
		return 1;
	}

	if (bmp->bmp_info_header->bit_count == 32) {
		fwrite(bmp->bmp_file_header, sizeof(BMPFileHeader), 1, file);
		fwrite(bmp->bmp_info_header, sizeof(BMPInfoHeader), 1, file);
		fwrite(bmp->bmp_color_header, sizeof(BMPColorHeader), 1, file);
		fwrite(bmp->data, bmp->data_size, 1, file);
	}
	else if (bmp->bmp_info_header->bit_count == 24) {
		fwrite(bmp->bmp_file_header, sizeof(BMPFileHeader), 1, file);
		fwrite(bmp->bmp_info_header, sizeof(BMPInfoHeader), 1, file);
		fwrite(bmp->data, bmp->data_size, 1, file);
	}
	else {
		return 1;
	}

	fclose(file);

	return 0;
}

void free_bmp(BMP* bmp) {
	if (bmp == NULL) {
		return;
	}

	free(bmp->bmp_file_header);
	free(bmp->bmp_info_header);
	free(bmp->bmp_color_header);
	free(bmp->data);
	free(bmp);
}

static int check_rgba_color_header(BMPColorHeader* bmp_color_header) {
	if (bmp_color_header == NULL) {
		return 1;
	}

	if (bmp_color_header->red_mask != BMP_RED_MASK ||
		bmp_color_header->blue_mask != BMP_BLUE_MASK ||
		bmp_color_header->green_mask != BMP_GREEN_MASK ||
		bmp_color_header->alpha_mask != BMP_ALPHA_MASK) {
		return 1;
	}

	if (bmp_color_header->color_space_type != BMP_SRGB_COLOR_SPACE) {
		return 1;
	}

	return 0;
}
