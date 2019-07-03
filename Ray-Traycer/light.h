#ifndef LIGHT
#define LIGHT

#include "vector3.h"
#include "color.h"

struct Light {
	Vector3 position;
	Color intensitySpecular;
	Color intensityDiffuse;
};

typedef struct Light Light;

Light* create_light(Vector3 position, Color intensitySpecular, Color intensityDiffuse);

#endif
