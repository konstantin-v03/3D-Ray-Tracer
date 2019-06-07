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
	Color temp;

	temp.r = color.r * t;
	temp.g = color.g * t;
	temp.b = color.b * t;

	return temp;
}

Color color_times_c(Color color1, Color color2) {
	Color temp;

	temp.r = color1.r * color2.r;
	temp.g = color1.g * color2.r;
	temp.b = color1.b * color2.r;

	return temp;
}

Color color_divide(Color color1, Color color2) {
	Color temp;

	temp.r = color1.r / color2.r;
	temp.g = color1.g / color2.r;
	temp.b = color1.b / color2.r;

	return temp;
}

Color color_plus(Color color1, Color color2) {
	Color temp;

	temp.r = color1.r + color2.r;
	temp.g = color1.g + color2.r;
	temp.b = color1.b + color2.r;

	return temp;
}

Color color_minus(Color color1, Color color2) {
	Color temp;

	temp.r = color1.r - color2.r;
	temp.g = color1.g - color2.r;
	temp.b = color1.b - color2.r;

	return temp;
}