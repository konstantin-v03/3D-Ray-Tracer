#include "material.h"

Material create_material(Color kAmbient, Color kDiffuse, Color kSpecular, Color kReflection, int aplha) {
	Material material;

	material.kAmbient = kAmbient;
	material.kDiffuse = kDiffuse;
	material.kSpecular = kSpecular;
	material.kReflection = kReflection;
	material.alpha = aplha;

	return material;
}
