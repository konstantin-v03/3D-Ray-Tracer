#define ARRAY_LIST_INITIAL_SIZE 16
#define ARRAY_LIST_SIZE_EXPAND_ADDEND 16

typedef struct {
	void** arr;
	int size;
	int filled_size;
} array_list;

array_list* array_list_init();

void array_list_add(array_list* array, void* ptr);

void* array_list_get(array_list* array, int index);

void array_list_remove(array_list* array, int index);