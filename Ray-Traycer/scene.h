#include "vector3.h"
#include "array_list.h"

struct image_plane {
	vector3* top_left;
	vector3* top_right;
	vector3* bottom_left;
	vector3* bottom_right;
};

typedef struct image_plane image_plane;

struct scene {
	vector3* camera;
	image_plane* image_plane;
	array_list* objects;
};

typedef struct scene scene;