#include <stddef.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../internal/array.h"
#include "array_test.h"

void init_arr_test(array_t *array, size_t capacity, array_type_t type, int version) {
    if (array == NULL) {
        printf("array %d is null\n", version);
        return;
    }
    if (array->capacity != capacity) {
        printf("array %d wrong capacity exp %zu got %zu\n", version, capacity, array->capacity);
        return;
    }
    if (array->size != 0) {
        printf("array %d wrong size exp %zu got %zu\n", version, (size_t)0, array->size);
        return;
    }
    if (array->elems == NULL) {
        printf("array %d elems are null\n", version);
        return;
    }
}

int arr_test() {
    size_t capacity = 10;
    array_t *array1 = array_new(capacity, INT);

    for (int i = 0; i < (int)capacity; i++) {
        int *ptr = malloc(sizeof(int));
        if (ptr == NULL) {
            printf("failed to allocate memory\n");
            exit(1);
        }
        *ptr = i;
        bool res = array_append(&array1, ptr);
        if (!res) {
            printf("could not append\n");
            exit(1);
        }

        if (*((int*)array1->elems[i]) != i) {
            printf("array 1 index %d not equal exp %d got %d\n", i, i, *((int*)array1->elems[i]));
            exit(1);
        }
    }

    if (array1->size != array1->capacity) {
        printf("array 1 size is not right exp %zu got %zu\n", array1->capacity, array1->size);
        exit(1);
    }

    // Testing resizing by appending beyond initial capacity
    for (int i = (int)capacity; i < (int)capacity + 5; i++) {
        int *ptr = malloc(sizeof(int));
        if (ptr == NULL) {
            printf("failed to allocate memory\n");
            exit(1);
        }
        *ptr = i;
        bool res = array_append(&array1, ptr);
        if (!res) {
            printf("could not append i %d\n", i);
            exit(1);
        }

        if (*((int*)array1->elems[i]) != i) {
            printf("array 1 index %d not equal exp %d got %d\n", i, i, *((int*)array1->elems[i]));
            exit(1);
        }
    }

    if (array1->size != capacity + 5) {
        printf("array 1 size is not right exp %zu got %zu\n", capacity + 5, array1->size);
        exit(1);
    }

    if (array1->capacity < capacity + 5) { 
        printf("array 1 capacity is not right, expected at least %zu got %zu\n", capacity + 5, array1->capacity);
        exit(1);
    }

    int removed[capacity + 5 - 4];
    int k = 0;
    for (int i = (int)array1->size - 1; i >= 0; i -= 4) {
        int *ptr = malloc(sizeof(int));
        if (ptr == NULL) {
            printf("failed to allocate memory\n");
            exit(1);
        }
        removed[k] = i;
        *ptr = i;

        bool res = array_remove(&array1, ptr);
        free(ptr);  
        if (!res) {
            printf("could not remove i %d\n", i);
            exit(1);
        }
        k++;
    }

    if (array1->size != capacity + 5 - k) {
        printf("array 1 size is not right exp %zu got %zu\n", capacity + 5 - k, array1->size);
        exit(1);
    }

    for (size_t i = 0; i < array1->size; i++) {
        for (int j = 0; j < k; j++) {
            if (removed[j] == *((int*)array1->elems[i])) {
                printf("array 1 index %zu not removed exp %d \n", i, removed[j]);
                exit(1);
            }
        }
    }

    int removed2[capacity + 5 - k];
    int l = 0;
    for (size_t i = 0; i < array1->size; i *= 2) {
        removed2[l] = *((int*)array1->elems[i]);

        bool res = array_remove_index(&array1, i);
        if (!res) {
            printf("could not remove i %zu\n", i);
            exit(1);
        }
        l++;
    }

    if (array1->size != capacity + 5 - k - l) {
        printf("array 1 size is not right exp %zu got %zu\n", capacity + 5 - k - l, array1->size);
        exit(1);
    }

    // Check if elements removed by index are not present
    for (size_t i = 0; i < array1->size; i++) {
        for (int j = 0; j < l; j++) {
            if (removed2[j] == *((int*)array1->elems[i])) {
                printf("array 1 index %zu not removed exp %d \n", i, removed2[j]);
                exit(1);
            }
        }
    }

    printf("tests passed\n");
    return 0;
}
