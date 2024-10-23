#include <stddef.h>

typedef enum HeapType {
    MIN,
    MAX
}heap_type_t;

typedef enum HeapElemChild {
    LEFT,
    RIGHT
}heap_elem_child_t;

typedef struct Heap {
    size_t **elems;
    size_t *root;
    heap_type_t type;
    int size;
    int capacity;
}heap_t;

heap_t *heap_new(int capacity, heap_type_t type);
void heap_init(heap_t *heap, int size, size_t **elems);
size_t heap_get_child(size_t index, heap_elem_child_t child);
int heap_get_parent(size_t index);
void heap_heapify_up(heap_t *heap, size_t index);
void heap_heapify_down(heap_t *heap, size_t index);
void heap_push(heap_t *heap, size_t *val);
size_t *heap_get_min(heap_t *heap);
size_t *heap_get_max(heap_t *heap);
void heap_print(heap_t *heap);

