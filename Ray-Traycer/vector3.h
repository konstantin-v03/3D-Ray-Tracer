struct vector3 {
	float x;
	float y;
	float z;
};

typedef struct vector3 vector3;

float vector_dot(vector3* vector1, vector3* vector2);

float vector_norm(vector3* vector);

vector3* vector_times(vector3* vector, float scalar);

vector3* vector_plus(vector3* vector1, vector3* vector2);

vector3* vector_minus(vector3* vector1, vector3* vector2);

vector3* vector_inverted(vector3* vector);

vector3* vector_normalized(vector3* vector);

vector3* vector_lerp(vector3* start, vector3* end, float t);

vector3* create_vector(int x, int y, int z);
