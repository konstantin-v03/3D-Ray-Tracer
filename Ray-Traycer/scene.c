#include <stdint.h>
#include "scene.h"

void free_scene(scene* scene) {
	if (scene == NULL)
		return;

	free(scene->camera);
	free(scene->image_plane);
	free(scene->objects);
	free(scene);
}