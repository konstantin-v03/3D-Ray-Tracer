#include "color.h"
#include "scene.h"

struct Ray_tracer{
	Scene* scene;
	int width;
	int height;
};

typedef struct Ray_tracer Ray_tracer;

void traced_colors(Scene* scene, Color** colors, int width, int height, int num_bounces, int num_samples_per_direction);
