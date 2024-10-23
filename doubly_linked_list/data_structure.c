#include "data_structure.h"
#include <stddef.h>
#include <stdlib.h>

node_t *node_new(size_t *val){
    if (val == NULL){
        return NULL;
    }

    node_t *node = malloc(sizeof(node_t));
    if (node == NULL){
        return NULL;
    }

    node->val = val;
    node->next = NULL;
    node->prev = NULL;

    return node;
}

list_t *list_new(){
    list_t *list = malloc(sizeof(list_t));
    if (list == NULL){
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

void list_add_front(list_t* list, size_t *val){
    if (list == NULL || val == NULL){
        return;
    }
    
    node_t *node = node_new(val);
    if (node == NULL){
        return;
    }

    list->size ++;
    if (list->head == NULL){
        list->head = list->tail = node;

        return;
    }

    node->next = list->head;
    list->head->prev = node;
    list->head = node;
}

void list_add_back(list_t* list, size_t *val){
    if (list == NULL || val == NULL){
        return;
    }

    node_t *node =node_new(val);
    if (node == NULL){
        return;
    }

    list->size ++;
    if (list->tail == NULL){
        list->tail = list->head = node;
        return;
    }

    node->prev = list->tail;
    list->tail->next = node;
    list->tail = node;
}

void list_add(list_t* list, size_t *needle, size_t *val){
    node_t *curr = node_find(list, needle);
    if (curr == NULL){
        return;
    }

    if (curr == list->tail){
        return list_add_back(list, val);
    }

    node_t *node = node_new(val);
    if (node == NULL){
        free(curr);
        return;
    }

    list->size ++;

    node->next = curr->next;
    if (curr->next != NULL){
        curr->next->prev = node;
    }

    node->prev = curr;
    curr->next = node;
}

size_t *list_delete_front(list_t* list){
    if (list == NULL || list->head == NULL){
        return NULL;
    }

    size_t *temp = list->head->val;
    list->size --;
    if (list->head == list->tail){
        list->head = list->tail = NULL;
        free(list->head);
        free(list->tail);
        return temp;
    }

    list->head->next->prev = NULL;

    list->head = list->head->next;

    return temp;
}

size_t *list_delete_back(list_t* list){
    if (list == NULL || list->tail == NULL){
        return NULL;
    }

    size_t *temp = list->tail->val;
    list->size --;

    if (list->tail == list->head){
        list->tail = list->head = NULL;
        free(list->tail);
        free(list->head);
        return temp;
    }

    list->tail->prev->next = NULL;

    list->tail = list->tail->prev;

    return temp;
}

size_t *list_delete(list_t* list, size_t *val){
    node_t *curr = node_find(list, val);
    if (curr == NULL){
        return NULL;
    }

    if (curr == list->head){
        return list_delete_front(list);
    }
    if (curr == list->tail){
        return list_delete_back(list);
    }

    list->size --;
    curr->next->prev = curr->prev;
    curr->prev->next = curr->next;

    curr->next = NULL;
    curr->prev = NULL;

    return curr->val;
}

node_t *node_find(list_t* list, size_t *val){
    if (list == NULL || val == NULL || list->head == NULL){
        return NULL;
    }

    node_t *curr = list->head;

    while (curr != NULL) {
        if (curr->val == val){
            return curr;
        }
        curr = curr->next;
    }

    return NULL;
}

