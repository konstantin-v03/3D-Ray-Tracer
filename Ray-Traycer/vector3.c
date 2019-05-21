#include <math.h>
#include "vector3.h"

float vector3_dot(Vector3* vector1, Vector3* vector2) {
	return vector1->x * vector2->x + vector1->y * vector2->y + vector1->z * vector2->z;
}

float vector3_norm(Vector3* vector) {
	return sqrt(vector3_dot(vector, vector));
}

Vector3* vector3_times(Vector3* vector, float scalar) {
	Vector3* temp = malloc(sizeof(Vector3));

	temp->x = vector->x * scalar;
	temp->y = vector->y * scalar;
	temp->z = vector->z * scalar;
	
	return temp;
}

Vector3* vector3_plus(Vector3* vector1, Vector3* vector2) {
	Vector3 *temp = malloc(sizeof(Vector3));

	temp->x = vector1->x + vector2->x;
	temp->y = vector1->y + vector2->y;
	temp->z = vector1->z + vector2->z;

	return temp;
}

Vector3* vector3_minus(Vector3* vector1, Vector3* vector2) {
	Vector3 *temp = malloc(sizeof(Vector3));

	temp->x = vector1->x - vector2->x;
	temp->y = vector1->y - vector2->y;
	temp->z = vector1->z - vector2->z;

	return temp;
}

Vector3* vector3_inverted(Vector3* vector) {
	return vector3_times(vector, -1);
}

Vector3* vector3_normalized(Vector3* vector) {
	return vector3_times(vector, 1 / norm(vector));
}

Vector3* vector3_lerp(Vector3* start, Vector3* end, float t) {
	Vector3* v1 = vector3_times(start, 1 - t);
	Vector3* v2 = vector3_times(end, t);
	Vector3* v3 = vector3_plus(v1, v2);

	free(v1);
	free(v2);

	return v3;
}

Vector3* create_vector3(int x, int y, int z) {
	Vector3* temp = malloc(sizeof(Vector3));

	temp->x = x;
	temp->y = y;
	temp->z = z;
	
	return temp;
}
