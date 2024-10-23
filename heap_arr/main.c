#include <stdio.h>
#include <stdlib.h>
#include "data_structure.h"

void test_min_heap();
void test_max_heap();
void test_heap_init();

int main() {
    printf("Running heap tests...\n");

    test_min_heap();

    test_max_heap();

    test_heap_init();

    printf("All tests passed!\n");
    return 0;
}

void test_min_heap() {
    printf("Testing MIN heap...\n");

    int capacity = 10;
    heap_t *min_heap = heap_new(capacity, MIN);

    size_t values[] = {10, 20, 5, 6, 1, 8};
    for (int i = 0; i < 6; i++) {
        heap_push(min_heap, &values[i]);
    }

    heap_print(min_heap);
    size_t *min_val = heap_get_min(min_heap);
    if (*min_val != 1) {
        printf("Test failed: Expected min value to be 1, but got %zu\n", *min_val);
        return;
    }

    printf("Min value: %zu (expected: 1)\n", *min_val);

    size_t new_value = 0;
    heap_push(min_heap, &new_value);

    min_val = heap_get_min(min_heap);
    if (*min_val != 0) {
        printf("Test failed: Expected min value to be 0 after push, but got %zu\n", *min_val);
        return;
    }

    printf("Min value after push: %zu (expected: 0)\n", *min_val);

    printf("MIN heap test passed!\n\n");
}

void test_max_heap() {
    printf("Testing MAX heap...\n");

    int capacity = 10;
    heap_t *max_heap = heap_new(capacity, MAX);

    size_t values[] = {10, 20, 5, 6, 1, 8};
    for (int i = 0; i < 6; i++) {
        heap_push(max_heap, &values[i]);
    }

    heap_print(max_heap);
    size_t *max_val = heap_get_max(max_heap);
    if (*max_val != 20) {
        printf("Test failed: Expected max value to be 20, but got %zu\n", *max_val);
        return;
    }

    printf("Max value: %zu (expected: 20)\n", *max_val);

    size_t new_value = 25;
    heap_push(max_heap, &new_value);

    max_val = heap_get_max(max_heap);
    if (*max_val != 25) {
        printf("Test failed: Expected max value to be 25 after push, but got %zu\n", *max_val);
        return;
    }

    printf("Max value after push: %zu (expected: 25)\n", *max_val);

    printf("MAX heap test passed!\n\n");
}

void test_heap_init() {
    printf("Testing heap initialization with heap_init...\n");

    int capacity = 10;
    heap_t *min_heap = heap_new(capacity, MIN);
    size_t *elems[] = {(size_t[]){1}, (size_t[]){6}, (size_t[]){5}, (size_t[]){10}, (size_t[]){20}, (size_t[]){8}};
    int size = 6;

    heap_init(min_heap, size, elems);
    heap_print(min_heap);

    size_t *min_val = heap_get_min(min_heap);

    if (*min_val != 1) {
        printf("Test failed: Expected min value to be 1 after heap_init, but got %zu\n", *min_val);
        return;
    }
    printf("Min value after heap_init: %zu (expected: 1)\n", *min_val);

    heap_t *max_heap = heap_new(capacity, MAX);

    heap_init(max_heap, size, elems);
    heap_print(max_heap);

    size_t *max_val = heap_get_max(max_heap);
    if (*max_val != 20) {
        printf("Test failed: Expected max value to be 20 after heap_init, but got %zu\n", *max_val);
        return;
    }
    printf("Max value after heap_init: %zu (expected: 20)\n", *max_val);

    printf("Heap initialization test passed!\n\n");
}
