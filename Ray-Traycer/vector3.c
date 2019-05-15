#include<math.h>

#include "vector3.h"

float vector_dot(vector3* vector1, vector3* vector2) {
	return vector1->x * vector2->x + vector1->y * vector2->y + vector1->z * vector2->z;
}

float vector_norm(vector3* vector) {
	return sqrt(vector_dot(vector, vector));
}

vector3* vector_times(vector3* vector, float scalar) {
	vector3 *temp = malloc(sizeof(vector3));

	temp->x = vector->x * scalar;
	temp->y = vector->y * scalar;
	temp->z = vector->z * scalar;
	
	return temp;
}

vector3* vector_plus(vector3* vector1, vector3* vector2) {
	vector3 *temp = malloc(sizeof(vector3));

	temp->x = vector1->x + vector2->x;
	temp->y = vector1->y + vector2->y;
	temp->z = vector1->z + vector2->z;

	return temp;
}

vector3* vector_minus(vector3* vector1, vector3* vector2) {
	vector3 *temp = malloc(sizeof(vector3));

	temp->x = vector1->x - vector2->x;
	temp->y = vector1->y - vector2->y;
	temp->z = vector1->z - vector2->z;

	return temp;
}

vector3* vector_inverted(vector3* vector) {
	return vector_times(vector, -1);
}

vector3* vector_normalized(vector3* vector) {
	return vector_times(vector, 1 / norm(vector));
}

vector3* vector_lerp(vector3* start, vector3* end, float t) {
	return vector_plus(vector_times(start, 1 - t), vector_times(end, t));
}

vector3* create_vector(int x, int y, int z) {
	vector3* temp = malloc(sizeof(vector3));

	temp->x = x;
	temp->y = y;
	temp->z = z;
	
	return temp;
}
