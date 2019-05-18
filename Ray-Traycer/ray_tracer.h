#include "color.h"
#include "scene.h"

struct ray_tracer{
	scene* scene;
	int width;
	int height;
};

typedef struct ray_tracer ray_tracer;

color* traced_value_at_pixel(ray_tracer* ray_tracer, int x, int y);