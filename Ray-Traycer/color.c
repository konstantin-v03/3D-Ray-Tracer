#include "color.h"

void color_clamped(color* color1) {

	if (color1->r < 0) {
		color1->r = 0;
	}
	else if (color1->r > MAX) {
		color1->r = MAX;
	}

	if (color1->b < 0) {
		color1->b = 0;
	}
	else if (color1->b > MAX) {
		color1->b = MAX;
	}

	if (color1->g < 0) {
		color1->g = 0;
	}
	else if (color1->g > MAX) {
		color1->g = MAX;
	}

}

color* color_times(color* color1, float t) {
	color* temp = malloc(sizeof(color));

	temp->r = color1->r * t;
	temp->g = color1->g * t;
	temp->b = color1->b * t;

	return temp;
}

color* color_times_c(color* color1, color* color2) {
	color* temp = malloc(sizeof(color));

	temp->r = color1->r * color2->r;
	temp->g = color1->g * color2->r;
	temp->b = color1->b * color2->r;

	return temp;
}

color*color_divide(color* color1, color* color2) {
	color* temp = malloc(sizeof(color));

	temp->r = color1->r / color2->r;
	temp->g = color1->g / color2->r;
	temp->b = color1->b / color2->r;

	return temp;
}

color* color_plus(color* color1, color* color2) {
	color* temp = malloc(sizeof(color));

	temp->r = color1->r + color2->r;
	temp->g = color1->g + color2->r;
	temp->b = color1->b + color2->r;

	return temp;
}

color* color_minus(color* color1, color* color2) {
	color* temp = malloc(sizeof(color));

	temp->r = color1->r - color2->r;
	temp->g = color1->g - color2->r;
	temp->b = color1->b - color2->r;

	return temp;
}