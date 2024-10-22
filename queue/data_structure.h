#include <stddef.h>

typedef struct Node node_t;

typedef struct Node{
    size_t *val;
    node_t *next;
}node_t;

typedef struct Queue{
    int size;
    node_t *head;
    node_t *tail;
}queue_t;

node_t *node_new(size_t *val, node_t *next);
queue_t *queue_new();
int queue_queue(queue_t *queue, size_t *val);
size_t *queue_dequeue(queue_t *queue);
size_t *queue_peak(queue_t *queue);
size_t *queue_get(queue_t *queue, int index);
