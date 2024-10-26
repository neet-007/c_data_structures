#include <stddef.h>

typedef struct LcpArray {
    int *elems;
    size_t size;
    size_t capacity;
} lcp_array_t;
