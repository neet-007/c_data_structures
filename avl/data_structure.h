#include <stddef.h>

typedef enum AvlMinMax {
    MIN,
    MAX
}avl_min_max_t;

typedef struct Node node_t;
typedef struct Node {
    node_t *parent;
    node_t *left;
    node_t *right;
    size_t height;
    int val;
}node_t;

typedef struct Avl{
    node_t *root;
    size_t size;
    int max;
    int min;
}avl_t;

node_t *node_new(int val, node_t *parent, node_t *left, node_t *right);
avl_t *avl_new();
void avl_insert(avl_t *avl, int val);
void avl_delete(avl_t *avl, int val);
node_t *avl_find(avl_t *bot, int val);
node_t *node_predecessor(avl_t *avl, node_t *node);
void avl_rotate(node_t *node);
void avl_rotate_line(node_t *node);
void avl_rotate_zig_zag(node_t *node);
void avl_print(node_t *node);
void avl_new_min_max(avl_t *avl, avl_min_max_t type);
