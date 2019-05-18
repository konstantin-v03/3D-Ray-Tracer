#define MAX 1

struct Color {
	float r;
	float g;
	float b;
};

typedef struct Color Color;

void color_clamped(Color* color);

Color* color_times(Color* color, float t);

Color* color_times_c(Color* color1, Color* color2);

Color* color_divide(Color* color1, Color* color2);

Color* color_plus(Color* color1, Color* color2);

Color* color_minus(Color* color1, Color* color2);
