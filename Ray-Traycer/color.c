#include "color.h"

void color_clamped(Color* color) {

	if (color->r < 0) {
		color->r = 0;
	}
	else if (color->r > MAX) {
		color->r = MAX;
	}

	if (color->b < 0) {
		color->b = 0;
	}
	else if (color->b > MAX) {
		color->b = MAX;
	}

	if (color->g < 0) {
		color->g = 0;
	}
	else if (color->g > MAX) {
		color->g = MAX;
	}

}

Color* color_times(Color* color, float t) {
	Color* temp = malloc(sizeof(Color));

	temp->r = color->r * t;
	temp->g = color->g * t;
	temp->b = color->b * t;

	return temp;
}

Color* color_times_c(Color* color1, Color* color2) {
	Color* temp = malloc(sizeof(Color));

	temp->r = color1->r * color2->r;
	temp->g = color1->g * color2->r;
	temp->b = color1->b * color2->r;

	return temp;
}

Color*color_divide(Color* color1, Color* color2) {
	Color* temp = malloc(sizeof(Color));

	temp->r = color1->r / color2->r;
	temp->g = color1->g / color2->r;
	temp->b = color1->b / color2->r;

	return temp;
}

Color* color_plus(Color* color1, Color* color2) {
	Color* temp = malloc(sizeof(Color));

	temp->r = color1->r + color2->r;
	temp->g = color1->g + color2->r;
	temp->b = color1->b + color2->r;

	return temp;
}

Color* color_minus(Color* color1, Color* color2) {
	Color* temp = malloc(sizeof(Color));

	temp->r = color1->r - color2->r;
	temp->g = color1->g - color2->r;
	temp->b = color1->b - color2->r;

	return temp;
}