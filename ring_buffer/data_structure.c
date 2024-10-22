#include "data_structure.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

ring_buffer_t *ring_buffer_new(int capacity) {
    if (capacity == 0) {
        return NULL;
    }

    ring_buffer_t *ring_buffer = malloc(sizeof(ring_buffer_t));
    if (ring_buffer == NULL) {
        return NULL;
    }

    ring_buffer->arr = calloc(capacity, sizeof(size_t *));
    if (ring_buffer->arr == NULL) {
        free(ring_buffer);
        return NULL;
    }

    ring_buffer->capacity = capacity;
    ring_buffer->head = -1;
    ring_buffer->tail = -1;
    ring_buffer->size = 0;

    return ring_buffer;
}

void ring_buffer_push(ring_buffer_t *ring_buffer, size_t *val) {
    if (ring_buffer == NULL || val == NULL) {
        return;
    }

    if (ring_buffer->tail == -1) {
        ring_buffer->tail = 0;
    } else {
        ring_buffer->tail = (ring_buffer->tail + 1) % ring_buffer->capacity;
    }

    if (ring_buffer->size == ring_buffer->capacity) {
        ring_buffer->head = (ring_buffer->head + 1) % ring_buffer->capacity;
    } else {
        if (ring_buffer->head == -1) {
            ring_buffer->head = 0;
        }
        ring_buffer->size++;
    }

    ring_buffer->arr[ring_buffer->tail] = val;
}

size_t *ring_buffer_pop(ring_buffer_t *ring_buffer) {
    if (ring_buffer == NULL || ring_buffer->size == 0) {
        return NULL;
    }

    if (ring_buffer->head == -1) {
        return NULL;
    }

    size_t *val = ring_buffer->arr[ring_buffer->head];

    if (ring_buffer->head == ring_buffer->tail) {
        ring_buffer->head = -1;
        ring_buffer->tail = -1;
    } else {
        ring_buffer->head = (ring_buffer->head + 1) % ring_buffer->capacity;
    }

    ring_buffer->size--;
    return val;
}

size_t *ring_buffer_front_peak(ring_buffer_t *ring_buffer) {
    if (ring_buffer == NULL || ring_buffer->size == 0 || ring_buffer->head == -1) {
        return NULL;
    }
    return ring_buffer->arr[ring_buffer->head];
}

size_t *ring_buffer_back_peak(ring_buffer_t *ring_buffer) {
    if (ring_buffer == NULL || ring_buffer->size == 0 || ring_buffer->tail == -1) {
        return NULL;
    }
    return ring_buffer->arr[ring_buffer->tail];
}
