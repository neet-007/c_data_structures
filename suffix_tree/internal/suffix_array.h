#include <stddef.h>
#include "array.h"

array_t *sort_chars(char *s, array_t *alphabet);
array_t *compute_classess(char *s, array_t *order);
bool sorting_doubles(char *s, size_t l, array_t **order, array_t *classes);
bool update_classes(char *s, size_t l, array_t *new_order, array_t **classes);
array_t *build_suffix_array(char *s, array_t *alphabet);
