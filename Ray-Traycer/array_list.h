#ifndef ARRAY_LIST
#define ARRAY_LIST

#define ARRAY_LIST_INITIAL_SIZE 16
#define ARRAY_LIST_SIZE_EXPAND_ADDEND 16

struct Array_list {
	void** arr;
	int size;
	int filled_size;
};

typedef struct Array_list Array_list;

Array_list* array_list_init();

void free_array_list(Array_list* array_list);

int array_list_size(Array_list* array_list);

void array_list_add(Array_list* array_list, void* ptr);

void* array_list_get(Array_list* array_list, int index);

void array_list_remove(Array_list* array_list, int index);

#endif 