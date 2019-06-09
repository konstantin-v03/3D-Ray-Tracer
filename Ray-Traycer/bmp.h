#ifndef BMP_
#define BMP_

#include <stdint.h>

#define BMP_MAGIC_NUMBER 19778

#define BMP_TYPE_RGB 1
#define BMP_TYPE_RGBA 2

#define BMP_RED_MASK 0x00ff0000
#define BMP_GREEN_MASK 0x0000ff00
#define BMP_BLUE_MASK 0x000000ff
#define BMP_ALPHA_MASK 0xff000000
#define BMP_SRGB_COLOR_SPACE 0x73524742


#pragma pack(push, 1)

struct BMPFileHeader {
	uint16_t file_type;
	uint32_t file_size;
	uint16_t reserved1;
	uint16_t reserved2;
	uint32_t offset_data;
};

typedef struct BMPFileHeader BMPFileHeader;

struct BMPInfoHeader {
	uint32_t size;                    
	int32_t width;                    
	int32_t height;                    
    uint16_t planes;                    
	uint16_t bit_count;            
	uint32_t compression;       
	uint32_t size_image;                
	int32_t x_pixels_per_meter;
	int32_t y_pixels_per_meter;
	uint32_t colors_used;               
	uint32_t colors_important;      
};

typedef struct BMPInfoHeader BMPInfoHeader;

struct BMPColorHeader {
	uint32_t red_mask;
	uint32_t green_mask;
	uint32_t blue_mask;
	uint32_t alpha_mask;
	uint32_t color_space_type;
	uint32_t unused[16];
};

typedef struct BMPColorHeader BMPColorHeader;

#pragma pack(pop)

struct BMP {
	BMPFileHeader* bmp_file_header;
	BMPInfoHeader* bmp_info_header;
	BMPColorHeader* bmp_color_header;

	int data_size;
	uint32_t* data;
};

typedef struct BMP BMP;

BMP* read_bmp_image(char* file_name);

int write_bmp_image(BMP* bmp, char* file_name);

void free_bmp(BMP* bmp);

#endif