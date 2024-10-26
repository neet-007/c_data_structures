#include <stddef.h>

typedef struct SuffixArray{
    int *elems;
    size_t size;
    size_t capacity;
} suffix_array_t;

int *sort_chars(char *s, char **alphabet);
int *compute_classess(char *s, int *order);
void sorting_doubles(char *s, size_t l, int *order, int *classes);
void update_classes(char *s, size_t l, int *new_order, int *classes);
