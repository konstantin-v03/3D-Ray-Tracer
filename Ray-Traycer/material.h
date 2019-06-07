#ifndef MATERIAL
#define MATERIAL

#include "color.h"

struct Material {
	Color kAmbient;
	Color kDiffuse;
	Color kSpecular;
	Color kReflection;
	int alpha;
};

typedef struct Material Material;

Material create_material(Color kAmbient, Color kDiffuse, Color kSpecular, Color kReflection, int aplha);

#endif