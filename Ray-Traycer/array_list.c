#include <stdint.h>
#include "array_list.h"

void array_list_expand(array_list* array);

array_list* array_list_init() {
	array_list* array = malloc(sizeof(array_list));

	array->size = ARRAY_LIST_INITIAL_SIZE;
	array->filled_size = 0;
	array->arr = calloc(array->size, sizeof(void*));

	return array;
}

void array_list_add(array_list* array, void* ptr) {
	if (array->filled_size >= array->size)
		array_list_expand(array);

	array->arr[array->filled_size] = ptr;
	array->filled_size++;
}

void* array_list_get(array_list* array, int index) {
	if (index < 0 || index >= array->filled_size)
		return NULL;
	return array->arr[index];
}

void array_list_remove(array_list* array, int index) {
	if (index < 0 || index >= array->filled_size)
		return;

	for (int i = index; i < array->filled_size - 1; i++) {
		array->arr[i] = array->arr[i + 1];
	}

	array->filled_size--;
}

static void array_list_expand(array_list* array) {
	void** arr1 = calloc((int)(array->size * ARRAY_LIST_SIZE_EXPAND_FACTOR), sizeof(void*));

	for (int i = 0; i < array->size; i++) {
		arr1[i] = array->arr[i];
	}
	
	free(array);

	array->arr = arr1;
}