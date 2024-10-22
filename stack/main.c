#include <stdio.h>
#include "data_structure.h"

int main(){
    stack_t *stack = stack_new(5);
    if (stack == NULL){
        printf("could not allocate stack\n");
        return 1;
    }

    for (int i = 0; i < 6; i++){
        stack_push(stack, i);
        if (i >= 5 ){
            if (stack->size != stack->capacity){
                printf("should not push %d v %d\n", stack->size, stack->capacity);
                return 1;
            }
            continue;
        }
        if (stack->arr[i] != i){
            printf("wrong push %zu v %d\n", stack->arr[i], i);
            return 1;
        }
        if (stack->size != i + 1){
            printf("size is not correct %d v %d\n", stack->size, i + 1);
            return 1;
        }
    }

    for (int i = 4; i > 0; i--){
        int *popped = (int *)stack_pop(stack);

        if (*popped != i){
            printf("items dont match %d v %d\n", *popped, i + 1);
            return 1;
        }

        if (stack->size != i){
            printf("size is not correct %d v %d\n", stack->size, i + 1);
            return 1;
        }
    }

    printf("success\n");
}
