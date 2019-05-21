#ifndef COLOR
#define COLOR

#include <stdint.h>

struct Color {
	float r;
	float g;
	float b;
};

typedef struct Color Color;

uint32_t rgba_from_color(float r, float g, float b);

Color* create_color(float r, float g, float b);

Color* color_times(Color* color, float t);

Color* color_times_c(Color* color1, Color* color2);

Color* color_divide(Color* color1, Color* color2);

Color* color_plus(Color* color1, Color* color2);

Color* color_minus(Color* color1, Color* color2);

#endif