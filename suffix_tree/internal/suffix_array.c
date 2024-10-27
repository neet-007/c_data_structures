#include "suffix_array.h"
#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

array_t *sort_chars(char *s, array_t *alphabet){
    if (s == NULL || alphabet == NULL){
        return NULL;
    }

    int s_len = strlen(s);
    int *zero = malloc(sizeof(int));
    if (zero == NULL){
        return NULL;
    }

    *zero = -1;
    array_t *order = array_new_zero((size_t)s_len, INT, zero);
    if (order == NULL){
        return NULL;
    }

    *zero = 0;

    array_t *count= array_new_zero(alphabet->size, INT, zero);
    if (count== NULL){
        array_free(&order);
        return NULL;
    }

    for (size_t i = 0; i < (size_t)s_len; i++) {
        int index = (int)(s[i]) - (*(int*)alphabet->elems[0]);  
        if (index >= 0 && index < alphabet->size) {  
            (*((int *)(count->elems[index])))++;
        }
    }
    
    for (size_t i = 1; i < alphabet->size; i++) {
        (*((int *)(count->elems[i]))) += (*((int *)(count->elems[i - 1])));
    }

    for (int i = s_len - 1; i >= 0; i--){
        int index = (int)(s[i]) - (*(int*)alphabet->elems[0]);  

        *((int *)(count->elems[index])) -= 1;

        int updated_count = *((int *)(count->elems[index]));

        *((int *)(order->elems[updated_count])) = i;
    }

    return order;
}
array_t *compute_classess(char *s, array_t *order){
    if (s == NULL || order == NULL){
        return NULL;
    }

    int s_len = strlen(s);
    int *zero = malloc(sizeof(int));
    if (zero == NULL){
        return NULL;
    }

    *zero = 0;

    array_t *classes= array_new_zero(s_len, INT, zero);
    if (classes== NULL){
        array_free(&order);
        return NULL;
    }

    for (size_t i = 1; i < order->size; i++){
        int index_1 = (*(int *)order->elems[i]);
        int index_2 = (*(int *)order->elems[i - 1]);

        if (s[index_1] != s[index_2]){
            (*(int *)classes->elems[index_1]) = (*(int *)classes->elems[index_2]) + 1;
            continue;
        }

        (*(int *)classes->elems[index_1]) = (*(int *)classes->elems[index_2]);
    } 

    return classes;
}

void sorting_doubles(char *s, size_t l, array_t **order, array_t *classes);
void update_classes(char *s, size_t l, array_t *new_order, array_t **classes);
array_t *build_suffix_array(char *s);
