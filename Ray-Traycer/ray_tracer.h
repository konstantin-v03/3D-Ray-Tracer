#include "color.h"
#include "scene.h"

struct Ray_tracer{
	Scene* scene;
	int width;
	int height;
};

typedef struct Ray_tracer Ray_tracer;

Color* traced_value_at_pixel(Ray_tracer* ray_tracer, int x, int y);