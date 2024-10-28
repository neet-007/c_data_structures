#include <stddef.h>
#include "array.h"

int compare_LCP(char *s, int i, int j, int lcp);
array_t *compute_LCP_array(char *s, array_t *suffix_array);
