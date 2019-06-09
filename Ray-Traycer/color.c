#include "color.h"

uint32_t rgba_from_color(float r, float g, float b) {
	return (int)(b * 255) + ((int)(g * 255) << 8) + ((int)(r * 255) << 16) + (255 << 24);
}

Color color_clamped(Color color) {
	if (color.r > 1) {
		color.r = 1;
	}
	else if(color.r < 0){
		color.r = 0;
	}

	if (color.b > 1) {
		color.b = 1;
	}
	else if (color.b < 0) {
		color.b = 0;
	}

	if (color.g > 1) {
		color.g = 1;
	}
	else if (color.g < 0) {
		color.g = 0;
	}

	return color;
}

Color create_color(float r, float g, float b) {
	Color color;

	color.r = r;
	color.g = g;
	color.b = b;

	return color;
}

Color color_times(Color color, float t) {
	color.r *= t;
	color.g *= t;
	color.b *= t;

	return color;
}

Color color_times_c(Color color1, Color color2) {
	color1.r *= color2.r;
	color1.g *= color2.g;
	color1.b *= color2.b;

	return color1;
}

Color color_divide(Color color1, Color color2) {
    color1.r /= color2.r;
	color1.g /= color2.g;
	color1.b /= color2.b;

	return color1;
}

Color color_plus(Color color1, Color color2) {
	color1.r += color2.r;
	color1.g += color2.g;
    color1.b += color2.b;

	return color1;
}

Color color_minus(Color color1, Color color2) {
	color1.r -= color2.r;
	color1.g -= color2.g;
	color1.b -= color2.b;

	return color1;
}