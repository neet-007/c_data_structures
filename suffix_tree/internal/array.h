#pragma once
#include <stddef.h>
#include <stdbool.h>

typedef enum ArrayType {
    INT,
    CHAR,
} array_type_t;

typedef struct Array {
    void **elems;
    size_t size;
    size_t capacity;
    array_type_t type;
} array_t;

array_t *array_new(size_t capacity, array_type_t type);
array_t *array_new_zero(size_t capacity, array_type_t type, void *zero);
void array_free(array_t **array);
int array_index_of(array_t *array, void *val);
bool array_append(array_t **array, void *val);
bool array_remove(array_t **array, void *val);
void *array_remove_index(array_t **array, size_t index);
bool array_resize(array_t **array);
bool array_copy(array_t **array, array_t *copy);
