#include <stdio.h>
#include <stdlib.h>
#include "data_structure.h"

int main(){
    queue_t *queue = queue_new();
    if (queue == NULL){
        printf("could not allocate queue\n");
        return 1;
    }

    for (int i = 0; i < 5; i++){
        size_t *i_p = malloc(sizeof(int));
        if (i_p == NULL){
            printf("could not allocate i\n");
            return 1;
        }

        *i_p = i;
        int res = queue_queue(queue, i_p);

        if (res == 0){
            printf("faild to queue\n");
            return 0;
        }

        size_t *peaked = queue_get(queue, i);

        if (peaked == NULL){
            printf("peake is null\n");
            return 1;
        }

        if (*peaked != *i_p){
            printf("peaked does not equal val peaked v val %zu v %zu\n", *peaked, *i_p);
            return 1;
        }

    }

    for (int i = 0; i < 5; i++){
        size_t *dequeued = queue_dequeue(queue);

        if (dequeued== NULL){
            printf("dequed is null\n");
            return 1;
        }

        size_t *i_p = malloc(sizeof(int));

        if (i_p == NULL){
            printf("could not allocate i\n");
            return 1;
        }

        *i_p = i;
        if (*dequeued != *i_p){
            printf("items dont match %zu v %zu\n", *dequeued, *i_p);
            return 1;
        }

        if (queue->size != 4 - i){
            printf("size is not correct %d v %d\n", queue->size, 4 - i);
            return 1;
        }
    }

    printf("success\n");
}
