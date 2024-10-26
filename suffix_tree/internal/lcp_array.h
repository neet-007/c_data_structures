#include <stddef.h>
#include "array.h"

int compareLCP(char *s, int i, int j, int lcp);
array_t *computeLCPArray(char *s, array_t **suffixArray);
