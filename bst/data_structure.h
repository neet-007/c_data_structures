#include <stddef.h>

typedef enum BstMinMax {
    MIN,
    MAX
}bst_min_max_t;

typedef struct Node node_t;
typedef struct Node {
    node_t *parent;
    node_t *left;
    node_t *right;
    int val;
}node_t;

typedef struct Bst{
    node_t *root;
    size_t size;
    int max;
    int min;
}bst_t;

node_t *node_new(int val, node_t *parent, node_t *left, node_t *right);
bst_t *bst_new();
void bst_insert(bst_t *bst, int val);
void bst_delete(bst_t *bst, int val);
node_t *bst_find(bst_t *bot, int val);
node_t *node_predecessor(bst_t *bst, node_t *node);
void bst_print(node_t *node);
void bst_new_min_max(bst_t *bst, bst_min_max_t type);
