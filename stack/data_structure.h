#include <stddef.h>
typedef struct Stack {
    int size;
    int capacity;
    size_t *arr;
}stack_t;

stack_t *stack_new(int capacity);
void stack_push(stack_t *stack, size_t elem);
size_t *stack_pop(stack_t *stack);
size_t *peak(stack_t *stack);
