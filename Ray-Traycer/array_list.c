#include <stdint.h>
#include "array_list.h"

void array_list_expand(Array_list* array);

Array_list* array_list_init() {
	Array_list* array_list = malloc(sizeof(Array_list));
	
	array_list->size = ARRAY_LIST_INITIAL_SIZE;
	array_list->filled_size = 0;
	array_list->arr = calloc(array_list->size, sizeof(void*));

	return array_list;
}

void free_array_list(Array_list* array_list) {
	if (array_list == NULL) {
		return;
	}

	free(array_list->arr);
}

int array_list_size(Array_list* array_list) {
	return array_list->filled_size;
}

void array_list_add(Array_list* array_list, void* ptr) {
	if (array_list->filled_size >= array_list->size)
		array_list_expand(array_list);

	array_list->arr[array_list->filled_size] = ptr;
	array_list->filled_size++;
}

void* array_list_get(Array_list* array_list, int index) {
	if (index < 0 || index >= array_list->filled_size)
		return NULL;
	return array_list->arr[index];
}

void array_list_remove(Array_list* array_list, int index) {
	if (index < 0 || index >= array_list->filled_size)
		return;

	for (int i = index; i < array_list->filled_size - 1; i++) {
		array_list->arr[i] = array_list->arr[i + 1];
	}

	array_list->filled_size--;
}

static void array_list_expand(Array_list* array_list) {
	int new_size = array_list->size + ARRAY_LIST_SIZE_EXPAND_ADDEND;

	void** arr1 = calloc(new_size, sizeof(void*));

	for (int i = 0; i < array_list->size; i++) {
		arr1[i] = array_list->arr[i];
	}

	free(array_list->arr);
	
	array_list->size = new_size;
	array_list->arr = arr1;
}