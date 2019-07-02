#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include "scene_object.h"
#include "ray_tracer.h"
#include "material.h"
#include "ray_hit.h"
#include "light.h"
#include "ray.h"

static Color color_from_ray_hit(Scene* scene, Ray ray, int numBounces);

static Color phong_lighting_at_point(Scene* scene, Scene_object* scene_object, Vector3 point, Vector3 normal, Vector3 view);

static Color traced_value_at_pixel(Ray_tracer* tracer, int x, int y, int numBounces);

static int is_point_in_shadow_from_light(Scene* scene, Scene_object* scene_object, Vector3 point, Light light);

void traced_scene(Scene* scene, Color** colors, int width, int height, int numBounces) {
	Ray_tracer tracer;

	tracer.width = width;
	tracer.height = height;
	tracer.scene = scene;

	scene->direction = vector3_normalized(vector3_lerp(vector3_lerp(tracer.scene->image_plane.top_left, tracer.scene->image_plane.top_right, 0.5),
		vector3_lerp(tracer.scene->image_plane.bottom_left, tracer.scene->image_plane.bottom_right, 0.5),
		0.5));

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			colors[i][j] = traced_value_at_pixel(&tracer, j, i, numBounces);
		}
	}
}

static Color traced_value_at_pixel(Ray_tracer* tracer, int x, int y, int numBounces) {
	float xt = (float)x / tracer->width;
	float yt = (float)y / tracer->height;

	Vector3 top = vector3_lerp(tracer->scene->image_plane.top_left, tracer->scene->image_plane.top_right, xt);

	Vector3 bottom = vector3_lerp(tracer->scene->image_plane.bottom_left, tracer->scene->image_plane.bottom_right, xt);

	Vector3 point = vector3_plus(vector3_lerp(bottom, top, yt), tracer->scene->camera);

	Color color = color_from_ray_hit(tracer->scene, create_ray(point, tracer->scene->direction), numBounces);

	return color_clamped(color);
}

static Color color_from_ray_hit(Scene* scene, Ray ray, int numBounces) {
	if (scene->objects->filled_size <= 0) {
		return COLOR_BLACK;
	}

	Array_list* objects = scene->objects;

	int count_objects = array_list_size(objects);
	
	Scene_object* scene_object;
	Ray_hit ray_hit; 
	float t;

	ray_hit.t = -1;

	for (int i = 0; i < count_objects; i++) {
		scene_object = array_list_get(objects, i);

		t = scene_object->earliest_intersection(scene_object, ray);

		if (t == -1) {
			continue;
		}

		if(ray_hit.t == -1 || t < ray_hit.t) {
			ray_hit.scene_object = scene_object;
			ray_hit.t = t;
		}
	}

	if (ray_hit.t == -1) {
		return COLOR_BLACK;
	}

	ray_hit.normalized = scene_object_normat_at(ray_hit.scene_object, ray_at(ray, ray_hit.t));

	Vector3 view = vector3_normalized(vector3_inverted(ray.dir));

	Vector3 point = ray_at(ray, ray_hit.t);

	Color color = phong_lighting_at_point(scene, ray_hit.scene_object, point, ray_hit.normalized, view);;

	if (numBounces > 0) {
		Vector3 reflection = vector3_minus(vector3_times(vector3_times(ray_hit.normalized, vector3_dot(view, ray_hit.normalized)), 2), view);

		Color reflectedColor = color_from_ray_hit(scene, create_ray(point, reflection), numBounces - 1);

		if (color_compare(reflectedColor, COLOR_NULL_INSTANCE) == 0) {
			color = color_plus(color, color_times_c(reflectedColor, ray_hit.scene_object->material.kReflection));
		}
	}

	return color;
}

static Color phong_lighting_at_point(Scene* scene, Scene_object* scene_object, Vector3 point, Vector3 normal, Vector3 view) {
	Light* light;
	Color lightContributions = { 0, 0, 0 };
	Vector3 l, r;
	Color diffuse, specular;

	for (int i = 0; i < scene->lights->filled_size; i++) {
		light = array_list_get(scene->lights, i);

		if (vector3_dot(vector3_minus(light->position, point), normal) < 0) {
			continue;
		}

		if (is_point_in_shadow_from_light(scene, scene_object, point, *light) == 1) {
			continue;
		}

		l = vector3_normalized(vector3_minus(light->position, point));

		r = vector3_minus(vector3_times(normal, (vector3_dot(l, normal) * 2)), l);

		diffuse = color_times(color_times_c(light->intensityDiffuse, scene_object->material.kDiffuse), vector3_dot(l, normal));

		specular = color_times(color_times_c(light->intensitySpecular, scene_object->material.kSpecular), pow(vector3_dot(r, view), scene_object->material.alpha));

		lightContributions = color_plus(lightContributions, color_plus(diffuse, specular));
	}

	return color_clamped(color_plus(lightContributions, color_times_c(scene_object->material.kAmbient, scene->kAmbientLight)));
}

static int is_point_in_shadow_from_light(Scene* scene, Scene_object* scene_object, Vector3 point, Light light) {
	Vector3 direction = vector3_minus(light.position, point);

	Ray shadowRay;
	shadowRay.dir = direction;
	shadowRay.origin = point;

	Scene_object* temp;

	for (int i = 0; i < scene->objects->filled_size; i++) {
		temp = array_list_get(scene->objects, i);

		if (temp == scene_object) {
			continue;
		}

		if (scene_object->earliest_intersection(temp, shadowRay) != -1 && scene_object->earliest_intersection(temp, shadowRay) < 1) {
			return 1;
		}
	}

	return 0;
}
