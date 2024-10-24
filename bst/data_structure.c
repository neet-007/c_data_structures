#include "data_structure.h"
#include <stddef.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

node_t *node_new(int val, node_t *parent, node_t *left, node_t *right) {
    node_t *node = malloc(sizeof(node_t));
    if (node == NULL) {
        return NULL;
    }

    node->val = val;
    node->parent = parent;
    node->left = left;
    node->right = right;

    return node;
}

bst_t *bst_new() {
    bst_t *bst = malloc(sizeof(bst_t));
    if (bst == NULL) {
        return NULL;
    }

    bst->size = 0;
    bst->root = NULL;
    bst->max = INT_MAX;
    bst->min = INT_MIN;

    return bst;
}

void bst_insert(bst_t *bst, int val) {
    if (bst == NULL) {
        return;
    }

    node_t *node = node_new(val, NULL, NULL, NULL);
    if (node == NULL) {
        return;
    }

    if (bst->root == NULL) {
        bst->size = 1;
        bst->root = node;
        bst->max = val;
        bst->min = val;
        return;
    }

    node_t *curr = bst->root;
    node_t *parent = NULL;

    while (curr != NULL) {
        parent = curr;
        if (val < curr->val) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }

    node->parent = parent;
    if (val < parent->val) {
        parent->left = node;
    } else {
        parent->right = node;
    }

    bst->size++;
    if (val > bst->max) {
        bst->max = val;
    }
    if (val < bst->min) {
        bst->min = val;
    }
}

node_t *bst_find(bst_t *bst, int val) {
    if (bst == NULL || bst->root == NULL) {
        return NULL;
    }

    node_t *curr = bst->root;

    while (curr) {
        if (curr->val == val) {
            return curr;
        } else if (val < curr->val) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }

    return NULL;
}

node_t *node_successor(bst_t *bst, node_t *node) {
    if (node == NULL) {
        return NULL;
    }

    if (node->right) {
        node_t *curr = node->right;
        while (curr->left) {
            curr = curr->left;
        }
        return curr;
    }

    node_t *parent = node->parent;
    while (parent && node == parent->right) {
        node = parent;
        parent = parent->parent;
    }

    return parent;
}

void bst_delete(bst_t *bst, int val) {
    if (bst == NULL || bst->root == NULL) {
        return;
    }

    node_t *node = bst_find(bst, val);
    if (node == NULL || node->val != val) {
        return;
    }

    if (node->left == NULL && node->right == NULL) {
        if (node == bst->root) {
            bst->root = NULL;
        } else if (node == node->parent->left) {
            node->parent->left = NULL;
        } else {
            node->parent->right = NULL;
        }

        if (node->val == bst->min){
            bst_new_min_max(bst, MIN);
        }
        if (node->val == bst->max){
            bst_new_min_max(bst, MAX);
        }

        free(node);
        bst->size--;
        return;
    }

    if (node->left == NULL || node->right == NULL) {
        node_t *child = node->left ? node->left : node->right;
        if (node == bst->root) {
            bst->root = child;
        } else if (node == node->parent->left) {
            node->parent->left = child;
        } else {
            node->parent->right = child;
        }
        child->parent = node->parent;

        if (node->val == bst->min){
            bst_new_min_max(bst, MIN);
        }
        if (node->val == bst->max){
            bst_new_min_max(bst, MAX);
        }

        free(node);
        bst->size--;
        return;
    }

    node_t *succ = node_successor(bst, node);
    if (succ == NULL) {
        return;
    }
    node->val = succ->val;
    bst_delete(bst, succ->val);  

    if (node->val == bst->min){
        bst_new_min_max(bst, MIN);
    }
    if (node->val == bst->max){
        bst_new_min_max(bst, MAX);
    }
}

void bst_print(node_t *node) {
    if (node == NULL) {
        return;
    }

    bst_print(node->left);   
    printf("%d \n", node->val);  
    bst_print(node->right);  
}

void bst_new_min_max(bst_t *bst, bst_min_max_t type){
    if (bst == NULL || bst->root == NULL){
        return;
    }

    node_t *curr = bst->root;
    switch (type) {
        case MIN:
            while (curr->right) {
                curr = curr->right;
            }
            bst->max = curr->val;
            return;
        case MAX:
            while (curr->left) {
                curr = curr->left;
            }
            bst->max = curr->val;
            return;
        default:
            return;
    }
}

