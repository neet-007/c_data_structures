#include "array.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

array_t *array_new(size_t capacity, array_type_t type) {
    if (capacity == 0) {
        return NULL;
    }

    array_t *arr = malloc(sizeof(array_t));
    if (arr == NULL) {
        return NULL;
    }

    arr->elems = calloc(capacity, sizeof(void *));  
    if (arr->elems == NULL) {
        free(arr);  
        return NULL;
    }

    arr->size = 0;            
    arr->capacity = capacity;
    arr->type = type;

    return arr;
}

array_t *array_new_zero(size_t capacity, array_type_t type, void *zero) {
    if (zero == NULL){
        return NULL;
    }

    array_t *array = array_new(capacity, type);
    if (array == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < array->capacity; i++) {
        void *ptr = NULL;
        switch (type) {
            case INT:
                ptr = malloc(sizeof(int));
                if (ptr == NULL) {
                    array_free(&array);
                    return NULL;
                }
                *((int *)ptr) = *((int *)zero); 
                break;

            case CHAR:
                ptr = malloc(sizeof(char));
                if (ptr == NULL) {
                    array_free(&array);
                    return NULL;
                }
                *((char *)ptr) = *((char *)zero); 
                break;

            default:
                array_free(&array);
                return NULL;
        }
        array->elems[i] = ptr;
    }

    return array;
}

void array_free(array_t **array) {
    if (array == NULL || *array == NULL) {
        return;
    }

    for (size_t i = 0; i < (*array)->size; i++) {
        free((*array)->elems[i]);
    }

    free((*array)->elems);

    free(*array);
    *array = NULL; 
}

int array_index_of(array_t *array, void *val) {
    if (array == NULL || val == NULL) {
        return -1;
    }

    switch (array->type) {
        case INT: {
            int val_int = *((int *)val);
            for (size_t i = 0; i < array->size; i++) {
                if (*((int *)array->elems[i]) == val_int) {
                    return (int)i;
                }
            }
            break;
        }
        case CHAR: {
            char val_char = *((char *)val);
            for (size_t i = 0; i < array->size; i++) {
                if (*((char *)array->elems[i]) == val_char) {
                    return (int)i;
                }
            }
            break;
        }
        default:
            break;
    }

    return -1;
}

bool array_append(array_t **array, void *val) {
    if (array == NULL || *array == NULL || val == NULL) {
        return false;
    }

    if ((*array)->size >= (*array)->capacity) {
        if (!array_resize(array)) { 
            return false; 
        }
    }

    (*array)->elems[(*array)->size++] = val; 

    return true;
}

bool array_remove(array_t **array, void *val){
    if (array == NULL || *array == NULL || val == NULL){
        return false;
    }

    int index = array_index_of(*array, val);
    if (index == -1){
        return false;
    }

    if (array_remove_index(array, (size_t)index) == NULL){
        return false;
    }

    return true;
}

void *array_remove_index(array_t **array, size_t index){
    if (array == NULL || *array == NULL || (* array)->size <= index){
        return NULL;
    }
    
    void *val= (*array)->elems[index];

    for (size_t i = index; i < (*array)->size - 1; i++){
        (*array)->elems[i] = (*array)->elems[i + 1];
    }

    (*array)->elems[--(*array)->size] = NULL;

    if ((*array)->size < (*array)->capacity / 4){
        array_resize(array);
    }

    return val;
}


bool array_resize(array_t **array) {
    if (array == NULL || *array == NULL) {
        return false;
    }

    array_t *old_array = *array;  
    array_t *new_array = NULL;

    size_t new_capacity = 1;

    if (old_array->size >= old_array->capacity){
        new_capacity = old_array->capacity * 2;
    }else if (old_array->capacity > 1){
        new_capacity = old_array->capacity / 2;
    }

    new_array = array_new(new_capacity, old_array->type);
    if (new_array == NULL) {
        return false; 
    }

    for (size_t i = 0; i < old_array->size; i++) {
        new_array->elems[i] = old_array->elems[i]; 
    }

    new_array->size = old_array->size;

    free(old_array->elems);
    free(old_array);

    *array = new_array; 
    return true;
}
