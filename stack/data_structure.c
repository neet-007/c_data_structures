#include "data_structure.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

stack_t *stack_new(int capacity){
    stack_t *stack = malloc(sizeof(stack_t));
    if (stack == NULL){
        return NULL;
    }

    stack->capacity = capacity;
    stack->arr = calloc(capacity, sizeof(size_t));
    if (stack->arr == NULL){
        free(stack);
        return  NULL;
    }

    return stack;
}

void stack_push(stack_t *stack, size_t elem){
    if (stack == NULL || stack->size >= stack->capacity){
        return;
    }

    stack->arr[stack->size++] = elem;
}

size_t *stack_pop(stack_t *stack){
    if (stack == NULL || stack->size == 0 || stack->capacity == 0){
        return NULL;
    }

    return &stack->arr[--stack->size]; 
}

size_t *peak(stack_t *stack){
    if (stack == NULL || stack->size == 0 || stack->capacity == 0){
        return NULL;
    }

    return &stack->arr[stack->size - 1]; 
}
