#include <stddef.h>

typedef struct RingBuffer {
    size_t **arr;
    int size;
    int capacity;
    int head;
    int tail;
}ring_buffer_t;

ring_buffer_t *ring_buffer_new(int capacity);
void ring_buffer_push(ring_buffer_t *ring_buffer, size_t *val);
size_t *ring_buffer_pop(ring_buffer_t *ring_buffer);
size_t *ring_buffer_front_peak(ring_buffer_t *ring_buffer);
size_t *ring_buffer_back_peak(ring_buffer_t *ring_buffer);

