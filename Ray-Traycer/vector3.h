#ifndef VECTOR3
#define VECTOR3

struct Vector3 {
	float x;
	float y;
	float z;
};

typedef struct Vector3 Vector3;

float vector3_dot(Vector3 vector1, Vector3 vector2);

float vector3_norm(Vector3 vector);

Vector3 vector3_times(Vector3 vector, float scalar);

Vector3 vector3_plus(Vector3 vector1, Vector3 vector2);

Vector3 vector3_minus(Vector3 vector1, Vector3 vector2);

Vector3 vector3_inverted(Vector3 vector);

Vector3 vector3_normalized(Vector3 vector);

Vector3 vector3_lerp(Vector3 start, Vector3 end, float t);

Vector3 create_vector3(int x, int y, int z);

#endif
