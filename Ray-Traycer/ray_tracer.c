#include <stdint.h>
#include "scene_object.h"
#include "ray_tracer.h"
#include "ray_hit.h"
#include "ray.h"
#include "material.h"
#include "light.h"
#include <math.h>
#include <stdio.h>

Color color_from_ray_hit(Scene* scene, Ray* ray);

Color traced_value_at_pixel(Ray_tracer* tracer, int x, int y) {
	float xt = (float)x / tracer->width;
	float yt = (float)y / tracer->height;

	Vector3 v = tracer->scene->camera;

	Vector3 top = vector3_lerp(tracer->scene->image_plane.top_left, tracer->scene->image_plane.top_right, xt);

	Vector3 bottom = vector3_lerp(tracer->scene->image_plane.bottom_left, tracer->scene->image_plane.bottom_right, xt);

	Vector3 point = vector3_lerp(top, bottom, yt);

	Vector3 dir = vector3_minus(point, tracer->scene->camera);

	Ray ray;
	ray.origin = point;
	ray.dir = dir;

	return color_from_ray_hit(tracer->scene, &ray);
}

static Color phong_lighting_at_point(Scene* scene, Scene_object* scene_object, Vector3 point, Vector3 normal, Vector3 view) {
	Light* light;
	Color lightContributions = {0, 0, 0};
	Vector3 l, r;
	Color diffuse, specular;

	for (int i = 0; i < scene->lights->filled_size; i++) {
		light = (Light*)array_list_get(scene->lights, i);
		
		if (vector3_dot(vector3_minus(light->position, point), normal) < 0){
			continue;
		}

		//printf("true\n");

		l = vector3_normalized(vector3_minus(light->position, point));

		r = vector3_minus(vector3_times(normal, (vector3_dot(l, normal) * 2)), l);

		diffuse = color_times(color_times_c(light->intensityDiffuse, scene_object->material.kDiffuse), vector3_dot(l, normal));

		float p = pow(vector3_dot(r, view), scene_object->material.alpha);

		specular = color_times(color_times_c(light->intensitySpecular, scene_object->material.kSpecular), p);
		
		lightContributions = color_plus(lightContributions, color_plus(diffuse, specular));
	}

	//printf("r %f g %f b %f \n", lightContributions.r, lightContributions.g, lightContributions.b);

	Color c2 = color_times_c(scene_object->material.kAmbient, scene->kAmbientLight);

	Color c1 = color_plus(lightContributions, c2);

	//printf("r %f g %f b %f \n", c1.r, c1.g, c1.b);

	//printf("r %f g %f b %f \n", c2.r, c2.g, c2.b);

	//printf("---\n");

	return color_clamped(c1);
}

static Color color_from_ray_hit(Scene* scene, Ray* ray) {
	if (scene->objects->filled_size <= 0) {
		return COLOR_NULL_INSTANCE;
	}

	Array_list* objects = scene->objects;

	int count_objects = array_list_size(objects);
	float(*earliest_intersection)(Scene_object* scene_object, Ray* ray);
	
	Scene_object* scene_object;
	Ray_hit ray_hit; 
	Color color;
	float t;

	ray_hit.t = -1;

	for (int i = 0; i < count_objects; i++) {
		scene_object = (Scene_object*)(array_list_get(objects, i));
		earliest_intersection = scene_object->earliest_intersection;

		t = earliest_intersection(scene_object, ray);

		if(t > 0 && t < ray_hit.t || t > 0 && ray_hit.t == -1) {
			ray_hit.scene_object = scene_object;
			ray_hit.t = t;
		}
	}

	if (ray_hit.t == -1) {
		return COLOR_NULL_INSTANCE;
	}

	ray_hit.normalized = scene_object_normat_at(ray_hit.scene_object, ray_at(ray, ray_hit.t));

	return phong_lighting_at_point(scene, ray_hit.scene_object, ray_at(ray, ray_hit.t), ray_hit.normalized, vector3_normalized(vector3_inverted(ray->dir)));
}