#include "suffix_array_test.h"
#include "../internal/suffix_array.h"
#include "../internal/array.h"
#include <stdio.h>
#include <stdlib.h>

void sort_chars_test(){
    char *s = "hellotest";
    array_t *alphabet = array_new(26, CHAR);

    for (char i = 97; i < 123; i++){
        char *c = (char *)malloc(sizeof(char));
        if (c == NULL){
            printf("could not allocate memory i %c\n", i);
            exit(1);
        }

        *c = i;
        array_append(&alphabet, c);
    }

    array_t *sorted = sort_chars(s, alphabet);
    if (sorted == NULL){
        exit(1);
    }

    char *exp = "ehllostt";
    for (size_t i = 0; i < sorted->size; i++){
        if (*((char*)sorted->elems[i]) != exp[(int)i]){
            printf("not sorder exp %c got %c\n", exp[(int)i], *((char*)sorted->elems[i]));
            exit(1);
        }
    }

    printf("test passed\n");

}
void compute_classess_test();
void sorting_doubles_test();
void update_classes_test();
void build_suffix_array_test();
