#include "array_list.h"
#include "vector3.h"

struct Image_plane {
	Vector3 top_left;
	Vector3 top_right;
	Vector3 bottom_left;
	Vector3 bottom_right;
};

typedef struct Image_plane Image_plane;

struct Scene {
	Vector3 camera;
	Image_plane image_plane;
	Color kAmbientLight;
	Array_list* objects;
	Array_list* lights;
};

typedef struct Scene Scene;