#include <stdlib.h>
#include <stdio.h>
#include "light.h"

Light* create_light(Vector3 position, Color intensitySpecular, Color intensityDiffuse) {
	Light* light = malloc(sizeof(Light));

    /*
    printf("%f %f %f\n", position.x, position.y, position.z);
    printf("%f %f %f\n", intensitySpecular.r, intensitySpecular.g, intensitySpecular.b);
    printf("%f %f %f\n---\n", intensityDiffuse.r, intensityDiffuse.g, intensityDiffuse.b); 
    */

	light->position = position;
	light->intensityDiffuse = intensityDiffuse;
	light->intensitySpecular = intensitySpecular;

	return light;
}
