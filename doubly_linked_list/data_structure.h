#include <stddef.h>

typedef struct Node node_t;
typedef struct Node {
    size_t *val;
    node_t *next;
    node_t *prev;
}node_t;

typedef struct List{
    node_t *head;
    node_t *tail;
    int size;
} list_t;

node_t *node_new(size_t *val);
list_t *list_new();
void list_add_front(list_t* list, size_t *val);
void list_add_back(list_t* list, size_t *val);
void list_add(list_t* list, size_t *needle, size_t *val);
size_t *list_delete_front(list_t* list);
size_t *list_delete_back(list_t* list);
size_t *list_delete(list_t* list, size_t *val);
node_t *node_find(list_t* list, size_t *val);


