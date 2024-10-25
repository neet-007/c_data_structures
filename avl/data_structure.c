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
    node->height = 0;

    return node;
}

avl_t *avl_new(){
    avl_t *avl = malloc(sizeof(avl_t));
    if (avl == NULL){
        return NULL;
    }

    avl->root = 0;
    avl->max = INT_MAX;
    avl->min = INT_MIN;
    avl->size = 0;

    return avl;;
}

void avl_insert(avl_t *avl, int val){
    if (avl == NULL){
        return;
    }

    node_t *node = node_new(val, NULL, NULL, NULL);
    if (node == NULL){
        return;
    }

    avl->size ++;
    if (avl->root == NULL){
        avl->root = node;
        avl->min = val;
        avl->max = val;

        return;
    }

    node_t *parent = NULL;
    node_t *curr = avl->root;

    while (curr) {
        curr->height ++;
        parent = curr;
        if (curr->val >= val){
            curr = curr->left;
            continue;
        }
        curr = curr->left;
    }

    if (parent == NULL){
        //should never happen
        return;
    }

    if (val > avl->max){
        avl->max = val;
    }
    if (val > avl->min){
        avl->min= val;
    }

    if (parent->val >= val){
        parent->left = node;

    }else{
        parent->right = node;
    }

    node->parent = parent;

    if (parent->left && parent->right && abs((int)parent->parent->right->height - (int)parent->parent->left->height) > 1){
        avl_rotate(parent);
    }
}

void avl_delete(avl_t *avl, int val);

node_t *avl_find(avl_t *avl, int val){
    if (avl == NULL || avl->root == NULL){
        return NULL;
    }

    node_t *curr = avl->root;

    while (curr) {
        if (curr->val == val){
            break;
        }
        if (curr->val > val){
            if (curr->left == NULL){
                break;
            }
            curr = curr->left;
            continue;
        }
        if (curr->right == NULL){
            break;
        }
        curr = curr->right;
    }

    return curr;
}

node_t *node_successor(avl_t *avl, node_t *node){
    if (avl == NULL || node == NULL){
        return NULL;
    }

    if (node->right == NULL){
        node_t *parent = node->parent;
        if (parent == NULL){
            return NULL;
        }
        node_t *curr= node;

        while (parent && parent->right == curr) {
            curr = parent;
            parent = parent->parent;
        }

        return curr;
    }
        
    node_t *curr = node->right;

    while (curr->left) {
        curr = curr->left;
    }

    return curr;
}

void avl_rotate(node_t *node){
    if (node == NULL){
        return;
    }

    if ((node->left && node->left->left) || (node->right && node->right->right)){
        return avl_rotate_line(node);
    }
    avl_rotate_zig_zag(node);
}

void avl_rotate_line(node_t *node){
    if (node == NULL){
        return;
    }

    if (node->left && node->left->left){
        node->parent->left = node->left;
        node->left->parent = node->parent;
        node->left->right = node;
        node->parent = node->left;
        node->left = NULL;

        return;
    }

    node->parent->right= node->right;
    node->right->parent = node->parent;
    node->right->right = node;
    node->parent = node->right;
    node->right= NULL;
}

void avl_rotate_zig_zag(node_t *node){
    if (node == NULL){
        return;
    }

    if (node->left && node->left->right){
        node->parent->left = node->left->right;
        node->left->right->parent = node->parent;
        node->left->right->left = node->left;
        node->left->right->right = node;
        node->parent = node->left->parent = node->left->right;
        node->left->right = NULL;
        node->left = NULL;
        return;
    }

    node->parent->left = node->right->left;
    node->right->left->parent = node->parent;
    node->right->left->right= node->right;
    node->right->left->left = node;
    node->parent = node->right->parent = node->right->left;
    node->right->left = NULL;
    node->right= NULL;
}

void avl_print(node_t *node);

void avl_new_min_max(avl_t *avl, avl_min_max_t type){
    if (avl == NULL || avl->root == NULL){
        return;
    }

    switch (type) {
        case MIN:{
                node_t *curr = avl->root;
                while (curr->left) {
                    curr = curr->left;
                }
                avl->min = curr->val;
            }   
            return;
        case MAX:{
                node_t *curr = avl->root;
                while (curr->right) {
                    curr = curr->right;
                }
                avl->max= curr->val;
            }
            return;
        default:
            return;
    }
}

