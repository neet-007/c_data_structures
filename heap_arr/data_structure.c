#include "data_structure.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

heap_t *heap_new(int capacity, heap_type_t type){
    heap_t *heap = malloc(sizeof(heap_t));
    if (heap == NULL){
        return NULL;
    }

    heap->elems = calloc(capacity, sizeof(size_t));
    if (heap->elems == NULL){
        free(heap);
        return NULL;
    }

    heap->capacity = capacity;
    heap->size = 0;
    heap->root = NULL;
    heap->type = type;

    return heap;
}

void heap_init(heap_t *heap, int size, size_t **elems){
    if (heap == NULL || elems == NULL || size > heap->capacity){
        return;
    }

    for (size_t i = 0; i < size; i++){
        heap->size ++;
        heap->elems[i] = elems[i];
    }

    for (size_t i = (size_t)(size / 2); i > 0 ; i--){
        heap_heapify_up(heap, i);
    }

    return;
}

size_t heap_get_child(size_t index, heap_elem_child_t child){
    switch (child) {
        case LEFT:
            return (size_t)((index * 2) + 1);
        case RIGHT:
            return (size_t)((index * 2) + 2);
        default:
            return -1;
    }
}

int heap_get_parent(size_t index) {
    if (index == 0) {
        return -1; 
    }
    return (index - 1) / 2;
}

void heap_heapify_up(heap_t *heap, size_t index){
    if (index >= heap->size){
        return;
    }

    switch (heap->type) {
        case MIN:{
            size_t i = index;
            int parent = heap_get_parent(i);

            while (parent > -1 && *heap->elems[i] < *heap->elems[parent]) {
                size_t *temp = heap->elems[i];
                heap->elems[i] = heap->elems[parent];
                heap->elems[parent] = temp;

                i = (size_t)parent;
                parent = heap_get_parent(parent);
            }
        }
        return;
        case MAX:{
            size_t i = index;
            int parent = heap_get_parent(i);

            while (parent > -1 && *heap->elems[i] > *heap->elems[parent]) {
                if (*heap->elems[i] == 20 || *heap->elems[parent] == 20){
                    printf("this one loop\n");
                }
                size_t *temp = heap->elems[i];
                heap->elems[i] = heap->elems[parent];
                heap->elems[parent] = temp;

                i = (size_t)parent;
                parent = heap_get_parent(parent);
            }
        }
        return;
        default:
            return;
    }

}

void heap_heapify_down(heap_t *heap, size_t index){
    if (heap == NULL){
        return;
    }

    size_t i = index;

    switch (heap->type) {
        case MIN:{
            while (1){
                size_t min_child = i;
                size_t left_child = heap_get_child(i, LEFT);
                if (left_child < heap->size && *heap->elems[left_child] < *heap->elems[min_child]){
                    min_child = left_child;
                }

                size_t right_child = heap_get_child(index, RIGHT);
                if (right_child < heap->size && *heap->elems[right_child] < *heap->elems[min_child]){
                    min_child = right_child;
                }

                if (min_child == i){
                    break;
                }

                size_t *temp = heap->elems[min_child];
                heap->elems[min_child] = heap->elems[i];
                heap->elems[i] = temp;

                i = min_child;
            }
        }
        return;
        case MAX:{
            while (1){
                size_t max_child = i;
                size_t left_child = heap_get_child(i, LEFT);
                if (left_child < heap->size && *heap->elems[left_child] > *heap->elems[max_child]){
                    max_child = left_child;
                }

                size_t right_child = heap_get_child(index, RIGHT);
                if (right_child < heap->size && *heap->elems[right_child] > *heap->elems[max_child]){
                    max_child = right_child;
                }

                if (max_child == i){
                    break;
                }

                size_t *temp = heap->elems[max_child];
                heap->elems[max_child] = heap->elems[i];
                heap->elems[i] = temp;

                i = max_child;
            }
        }
        return;
        default:
            return;
    }

}

void heap_push(heap_t *heap, size_t *val){
    if (heap == NULL || val == NULL || heap->size >= heap->capacity){
        return;
    }

    heap->elems[heap->size] = val;
    heap_heapify_up(heap, heap->size++);

    return;
}

size_t *heap_get_min(heap_t *heap){
    if (heap == NULL || heap->type != MIN || heap->size == 0){
        return NULL;
    }

    size_t *temp = heap->elems[0];
    heap->elems[0] = heap->elems[--heap->size];

    heap_heapify_down(heap, 0);

    return temp;
}

size_t *heap_get_max(heap_t *heap){
    if (heap == NULL || heap->type != MAX || heap->size == 0){
        return NULL;
    }

    size_t *temp = heap->elems[0];
    heap->elems[0] = heap->elems[--heap->size];

    heap_heapify_down(heap, 0);

    return temp;
}

void heap_print(heap_t *heap){
    if (heap == NULL){
        return;
    }

    if (heap->type == MIN){
        printf("min heap...\n");
    }else{
        printf("max heap...\n");
    }
    for (size_t i = 0; i < heap->size; i++){
        printf("%zu ", *heap->elems[i]);
    }
    printf("\n");
}
