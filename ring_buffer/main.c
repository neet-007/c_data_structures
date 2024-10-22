#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "data_structure.h" 

int main() {
    printf("Test 1: Initialization\n");
    ring_buffer_t *rb = ring_buffer_new(3);
    if (rb->capacity == 3 && rb->head == -1 && rb->tail == -1) {
        printf("Initialization Passed\n");
    } else {
        printf("Initialization Failed: Expected capacity = 3, head = -1, tail = -1. Got capacity = %d, head = %d, tail = %d\n", rb->capacity, rb->head, rb->tail);
    }

    printf("\nTest 2: Push and Front/Back Peak\n");
    size_t val1 = 10, val2 = 20, val3 = 30;
    ring_buffer_push(rb, &val1);
    ring_buffer_push(rb, &val2);
    ring_buffer_push(rb, &val3);

    size_t *peaked = ring_buffer_front_peak(rb);
    size_t *peaked_back = ring_buffer_back_peak(rb);

    if (*peaked == 10 && *peaked_back == 30) {
        printf("Push and Peak Passed\n");
    } else {
        printf("Push and Peak Failed: Front peek expected %d, got %zu; Back peek expected %d, got %zu\n", 10, *peaked, 30, *peaked_back);
    }

    printf("\nTest 3: Buffer Full State and Overwrite\n");
    size_t val4 = 40;
    ring_buffer_push(rb, &val4); 
    
    peaked = ring_buffer_front_peak(rb);
    peaked_back = ring_buffer_back_peak(rb);
    if (*peaked == 20 && *peaked_back == 40) {
        printf("Buffer Full and Overwrite Passed\n");
    } else {
        printf("Buffer Full and Overwrite Failed: Front peek expected %d, got %zu; Back peek expected %d, got %zu\n", 20, *peaked, 40, *peaked_back);
    }

    printf("\nTest 4: Pop Operation\n");
    size_t *popped = ring_buffer_pop(rb);
    peaked = ring_buffer_front_peak(rb);
    if (*popped == 20 && *peaked == 30) {
        printf("Pop Passed\n");
    } else {
        printf("Pop Failed: Popped expected %d, got %zu; Front peek expected %d, got %zu\n", 20, *popped, 30, *peaked);
    }

    printf("\nTest 5: Empty Buffer Pop\n");
    ring_buffer_pop(rb); 
    ring_buffer_pop(rb); 

    popped = ring_buffer_pop(rb);
    if (popped == NULL) {
        printf("Empty Buffer Pop Passed\n");
    } else {
        printf("Empty Buffer Pop Failed: Expected %p, got %p\n", NULL, popped);
    }

    printf("\nTest 6: Peek on Empty Buffer\n");
    if (ring_buffer_front_peak(rb) == NULL && ring_buffer_back_peak(rb) == NULL) {
        printf("Peek on Empty Buffer Passed\n");
    } else {
        printf("Peek on Empty Buffer Failed: Expected NULL for both front and back peaks\n");
    }

    printf("\nTest 7: Push After Empty\n");
    ring_buffer_push(rb, &val1); 
    if (*ring_buffer_front_peak(rb) == 10 && *ring_buffer_back_peak(rb) == 10) {
        printf("Push After Empty Passed\n");
    } else {
        printf("Push After Empty Failed: Front peek expected %d, got %zu; Back peek expected %d, got %zu\n", 10, *ring_buffer_front_peak(rb), 10, *ring_buffer_back_peak(rb));
    }

    printf("\nTest 8: Wrap Around\n");
    ring_buffer_push(rb, &val2);
    ring_buffer_push(rb, &val3);
    ring_buffer_push(rb, &val4); 

    if (*ring_buffer_front_peak(rb) == 20 && *ring_buffer_back_peak(rb) == 40) {
        printf("Wrap Around Passed\n");
    } else {
        printf("Wrap Around Failed: Front peek expected %d, got %zu; Back peek expected %d, got %zu\n", 20, *ring_buffer_front_peak(rb), 40, *ring_buffer_back_peak(rb));
    }

    free(rb->arr);
    free(rb);
    
    return 0;
}
