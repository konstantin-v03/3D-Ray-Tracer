#ifndef MATERIAL
#define MATERIAL

#include "color.h"

struct Material {
	Color kAmbient;
	Color kDiffuse;
	Color kSpecular;
	Color kReflection;
};

typedef struct Material Material;

#endif