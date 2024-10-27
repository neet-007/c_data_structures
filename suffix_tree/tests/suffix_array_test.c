#include "suffix_array_test.h"
#include "../internal/suffix_array.h"
#include "../internal/array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        printf("sorted is null");
        exit(1);
    }

    if (sorted->size != strlen(s)){
        printf("size of sorted %zu does not equal size of s %zu", sorted->size, strlen(s));
        exit(1);
    }

    char *exp = "eehllostt";
    for (size_t i = 0; i < sorted->size; i++){
        if (s[*((int*)sorted->elems[i])] != exp[(int)i]){
            printf("not sorder exp %c got %c\n", exp[(int)i], s[*((int*)sorted->elems[i])]);
            exit(1);
        }
    }


    printf("sorted chars test passed\n");

}
void compute_classess_test(){
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

    array_t *order = sort_chars(s, alphabet);
    if (order== NULL){
        printf("order is null\n");
        exit(1);
    }

    if (order->size != strlen(s)){
        printf("size of sorted %zu does not equal size of s %zu\n", order->size, strlen(s));
        exit(1);
    }

    array_t *classes = compute_classess(s, order);
    if (order== NULL){
        printf("classes is null\n");
        exit(1);
    }

    if (classes->size != order->size){
        printf("size of sorted %zu does not equal size of s %zu\n", order->size, order->size);
        exit(1);
    }

    int exp[9] = {1, 0, 2, 2, 3, 5, 0, 4, 5}; 

    printf("what \n");
    for (size_t i = 0; i < classes->size; i++){
        if ((*(int *)classes->elems[i]) != exp[(int)i]){
            printf("clasess i %zu not equal exp %d got %d\n", i, exp[(int)i], (*(int *)classes->elems[i]));
            exit(1);
        }
    }

    printf("compute classes test passed\n");

}
void sorting_doubles_test(){
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

    array_t *order = sort_chars(s, alphabet);
    if (order== NULL){
        printf("order is null\n");
        exit(1);
    }

    if (order->size != strlen(s)){
        printf("size of sorted %zu does not equal size of s %zu\n", order->size, strlen(s));
        exit(1);
    }

    array_t *classes = compute_classess(s, order);
    if (order== NULL){
        printf("classes is null\n");
        exit(1);
    }

    if (classes->size != order->size){
        printf("size of classes %zu does not equal size of s %zu\n", order->size, order->size);
        exit(1);
    }

    bool res = sorting_doubles(s, (size_t)6, &order, classes);

    if (res == false){
        printf("faaaalse\n");
        exit(1);
    }

    if (order == NULL){
        printf("sorting doubles is null");
        exit(1);
    }

    if (order->size != strlen(s)){
        printf("sorting doubles size %zu != s len %zu", order->size, strlen(s));
        exit(1);
    }

    int exp[9]= { 6, 1, 0, 3, 2, 4, 7, 5, 8 };
    //int exp[9] = {6, 1, 0, 2, 3, 4, 7, 5, 8 };
    //int exp[9] = {1, 6, 0, 2, 3, 4, 7, 8, 5 };

    for (size_t i = 0; i < classes->size; i++){
        if ((*(int *)order->elems[i]) != exp[(int)i]){
            printf("souring doulbes %zu not equal exp %d got %d\n", i, exp[(int)i], (*(int *)order->elems[i]));
            exit(1);
        }
    }

    printf("soerting doulbes test passed\n");
}

void update_classes_test(){
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

    array_t *order = sort_chars(s, alphabet);
    if (order== NULL){
        printf("order is null\n");
        exit(1);
    }

    if (order->size != strlen(s)){
        printf("size of sorted %zu does not equal size of s %zu\n", order->size, strlen(s));
        exit(1);
    }

    array_t *classes = compute_classess(s, order);
    if (order== NULL){
        printf("classes is null\n");
        exit(1);
    }

    if (classes->size != order->size){
        printf("size of classes %zu does not equal size of s %zu\n", order->size, order->size);
        exit(1);
    }

    bool res = sorting_doubles(s, (size_t)6, &order, classes);

    if (res == false){
        printf("faaaalse\n");
        exit(1);
    }

    if (order == NULL){
        printf("sorting doubles is null");
        exit(1);
    }

    if (order->size != strlen(s)){
        printf("sorting doubles size %zu != s len %zu", order->size, strlen(s));
        exit(1);
    }

    res = update_classes(s, 2, order, &classes);

    if (res == false){
        printf("update classes false\n");
        exit(1);
    }

    if (classes == NULL){
        printf("update classs is null\n");
        exit(1);
    }

    if (classes->size != strlen(s)){
        printf("update classes size %zu vs les str %zu \n", classes->size, strlen(s));
        exit(1);
    }

    int exp[9]= { 2, 0, 3, 4, 5, 8, 1, 6, 7};
    //int exp[9] = {6, 1, 0, 2, 3, 4, 7, 5, 8 };
    //int exp[9] = {1, 6, 0, 2, 3, 4, 7, 8, 5 };

    for (size_t i = 0; i < classes->size; i++){
        printf("%zu %d v %d\n", i, exp[(int)i], (*(int *)classes->elems[i]));
    }

    for (size_t i = 0; i < classes->size; i++){
        if ((*(int *)classes->elems[i]) != exp[(int)i]){
            printf("updating classes %zu not equal exp %d got %d\n", i, exp[(int)i], (*(int *)classes->elems[i]));
            exit(1);
        }
    }

    printf("updating classes test passed\n");
}

void build_suffix_array_test();
