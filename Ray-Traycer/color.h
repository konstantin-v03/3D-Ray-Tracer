#define MAX 1

struct color_ {
	float r;
	float g;
	float b;
};

typedef struct color_ color;

void color_clamped(color* color1);

color* color_times(color* color1, float t);

color* color_times_c(color* color1, color* color2);

color* color_divide(color* color1, color* color2);

color* color_plus(color* color1, color* color2);

color* color_minus(color* color1, color* color2);
