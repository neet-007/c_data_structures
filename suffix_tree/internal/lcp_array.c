#include "lcp_array.h"
#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_LCP(char *s, int i, int j, int lcp) {
    int local_lcp = lcp > 0 ? lcp : 0;
    int len_s = strlen(s);

    while (i + local_lcp < len_s && j + local_lcp < len_s && s[i + local_lcp] == s[j + local_lcp]) {
        local_lcp++;
    }

    return local_lcp;
}

array_t *compute_LCP_array(char *s, array_t *suffix_array){
    if (s == NULL || suffix_array == NULL){
        return NULL;
    }
    
    int *zero = malloc(sizeof(int));
    if (zero == NULL){
        return NULL;
    }
    *zero = 0;

    array_t *inverse_suffix_array = array_new_zero(suffix_array->capacity, suffix_array->type, zero);
    if (inverse_suffix_array == NULL){
        free(zero);
        return NULL;
    }

    array_t *lcp_array = array_new_zero(suffix_array->size - 1, suffix_array->type, zero);
    if (inverse_suffix_array == NULL){
        free(zero);
        return NULL;
    }

    for (size_t i = 0; i < inverse_suffix_array->size; i++){
        (*(int *)inverse_suffix_array->elems[(*(int *)suffix_array->elems[i])]) = i;
    }

    int s_len = strlen(s);
    int lcp = 0;
    int suffix = (*(int *)suffix_array->elems[0]);
    
    for (size_t i = 0; i < suffix_array->size; i++){
        int curr_index = (*(int *)inverse_suffix_array->elems[suffix]);

        if (curr_index == s_len - 1){
            lcp = 0;
            suffix = (suffix + 1) % s_len;
            continue;
        }

        int next_index = (*(int *)suffix_array->elems[curr_index + 1]);
        lcp = compare_LCP(s, suffix, next_index, lcp - 1);
        (*(int *)lcp_array->elems[curr_index])= lcp;

        suffix = (suffix + 1) % s_len;
    }

    return lcp_array;
}
