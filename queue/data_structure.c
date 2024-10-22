#include "data_structure.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

node_t *node_new(size_t *val, node_t *next) {
    node_t *node = malloc(sizeof(node_t));
    if (node == NULL) {
        return NULL; 
    }
    
    node->val = val; 
    node->next = next; 
    return node;
}

queue_t *queue_new() {
    queue_t *queue = malloc(sizeof(queue_t));
    if (queue == NULL) {
        return NULL;
    }

    queue->size = 0;
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}

int queue_queue(queue_t *queue, size_t *val) {
    if (queue == NULL || val == NULL) {
        return 0;
    }

    node_t *node = node_new(val, NULL);
    if (node == NULL) {
        return 0; 
    }
    
    queue->size++;
    if (queue->head == NULL) {
        queue->head = node; 
        queue->tail = node;
        return 1;
    }

    queue->tail->next = node; 
    queue->tail = node; 

    return 1;
}

size_t *queue_dequeue(queue_t *queue) {
    if (queue == NULL || queue->size == 0) {
        return NULL;
    }

    size_t *temp = queue->head->val;
    node_t *old_head = queue->head;
    queue->head = queue->head->next;
    free(old_head); 
    queue->size--;

    if (queue->size == 0) {
        queue->tail = NULL;
        free(queue->tail);
    }

    return temp;
}

size_t *queue_peak(queue_t *queue) {
    if (queue == NULL || queue->size == 0) {
        return NULL;
    }

    return queue->head->val;
}

size_t *queue_get(queue_t *queue, int index) {
    if (queue == NULL || queue->size == 0) {
        return NULL;
    }

    int count = 0;
    node_t *curr = queue->head;

    while (curr != NULL && count != index) {
        curr = curr->next;
        count++;
    }

    return curr ? curr->val : NULL; 
}
