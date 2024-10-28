#include "lcp_array_test.h"
#include "../internal/array.h"
#include "../internal/suffix_array.h"
#include "../internal/lcp_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void compute_LCP_array_test(){
    char *s = "hellotest";

    array_t *alphabet = array_new(26, CHAR);

    for (char i = 97; i < 123; i++){
        char *c = (char *)malloc(sizeof(char));
        if (c == NULL){
            array_free(&alphabet);
            free(s);
            printf("could not allocate memory i %c\n", i);
            exit(1);
        }

        *c = i;
        array_append(&alphabet, c);
    }

    array_t *suffix_array = build_suffix_array(s, alphabet);

    if (suffix_array == NULL){
        printf("suffix array is nul\n");
        array_free(&suffix_array);
        array_free(&alphabet);
        free(s);
        exit(1);
    }

    if (strlen(s) != suffix_array->size){
        printf("suffix array size wrong exp %zu got %zu\n", strlen(s), suffix_array->size);
        array_free(&suffix_array);
        array_free(&alphabet);
        free(s);
        exit(1);
    }

    array_t *lcp_array = compute_LCP_array(s, suffix_array);

    if (lcp_array == NULL){
        printf("lcp array is nul\n");
        array_free(&suffix_array);
        array_free(&lcp_array);
        array_free(&alphabet);
        free(s);
        exit(1);
    }
 
    if (strlen(s) - 1 != lcp_array->size){
        printf("suffix array size wrong exp %zu got %zu\n", strlen(s) - 1, lcp_array->size);
        array_free(&suffix_array);
        array_free(&lcp_array);
        array_free(&alphabet);
        free(s);
        exit(1);
    }

    int exp[9] = { 1, 0, 0, 1, 0, 0, 0, 1 };

    for (size_t i = 0; i < lcp_array->size; i++){
            printf("lcp array %d\n", (*(int *)lcp_array->elems[i]));
    }

    for (size_t i = 0; i < lcp_array->size; i++){
        if ((*(int *)lcp_array->elems[i]) != exp[i]){
            printf("lcp array %zu not equal %d v %d\n", i, (*(int *)lcp_array->elems[i]), exp[i]);
            exit(1);
        }
    }

    printf("lcp array test passed\n");
    array_free(&suffix_array);
    array_free(&lcp_array);
    array_free(&alphabet);
    free(s);
}
