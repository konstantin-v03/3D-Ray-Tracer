#define ARRAY_LIST_INITIAL_SIZE 16
#define ARRAY_LIST_SIZE_EXPAND_ADDEND 16

struct Array_list {
	void** arr;
	int size;
	int filled_size;
};

typedef struct Array_list Array_list;

Array_list* array_list_init();

void array_list_add(Array_list* array, void* ptr);

void* array_list_get(Array_list* array, int index);

void array_list_remove(Array_list* array, int index);