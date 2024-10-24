#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include "data_structure.h"

void assert_int_equal(int actual, int expected, const char *message) {
    if (actual != expected) {
        printf("%s - Expected: %d, Got: %d\n", message, expected, actual);
    } else {
        printf("%s - Passed\n", message);
    }
}

void assert_node_found(node_t *node, int val, const char *message) {
    if (node == NULL) {
        printf("%s - Node is NULL, test failed\n", message);
    }else if (node->val != val) {
        printf("%s - exp %d found %d, test failed\n", message, val, node->val);
    }else {
        printf("%s - Passed\n", message);
    }
}

void assert_node_not_found(node_t *node, int val, const char *message){
    if (node == NULL) {
        printf("%s - Node is NULL, test passed\n", message);
    }else if (node->val != val) {
        printf("%s - found node but not equal, test passed\n", message);
    }else {
        printf("%s - found node, test failed\n", message);
    }
}
void assert_node_null(node_t *node, const char *message) {
    if (node != NULL) {
        printf("%s - Node is NOT NULL, test failed\n", message);
    } else {
        printf("%s - Passed\n", message);
    }
}

void test_bst_insert_and_find() {
    bst_t *bst = bst_new();
    
    bst_insert(bst, 10);
    bst_insert(bst, 5);
    bst_insert(bst, 15);
    
    node_t *node1 = bst_find(bst, 10);
    node_t *node2 = bst_find(bst, 5);
    node_t *node3 = bst_find(bst, 15);
    node_t *node4 = bst_find(bst, 100);

    assert_node_found(node1, 10, "Find node with value 10");
    assert_node_found(node2, 5, "Find node with value 5");
    assert_node_found(node3, 15, "Find node with value 15");
    assert_node_not_found(node4, 100, "Find non-existent node with value 100");
}

void test_bst_min_max() {
    bst_t *bst = bst_new();
    
    bst_insert(bst, 20);
    bst_insert(bst, 10);
    bst_insert(bst, 30);
    
    assert_int_equal(bst->min, 10, "Check minimum value");
    assert_int_equal(bst->max, 30, "Check maximum value");
}

void test_bst_delete() {
    bst_t *bst = bst_new();
    
    bst_insert(bst, 10);
    bst_insert(bst, 5);
    bst_insert(bst, 15);
    
    bst_delete(bst, 5);
    bst_delete(bst, 10);
    
    node_t *node1 = bst_find(bst, 10);
    node_t *node2 = bst_find(bst, 5);
    node_t *node3 = bst_find(bst, 15);
    
    assert_node_not_found(node1, 10, "Check if node 10 is deleted");
    assert_node_not_found(node2, 5, "Check if node 5 is deleted");
    assert_node_found(node3, 15, "Check if node 15 still exists");
}

void test_bst_edge_cases() {
    bst_t *bst = bst_new();
    
    bst_insert(bst, 10);
    bst_insert(bst, 10); 
    
    assert_int_equal(bst->size, 2, "BST size after inserting duplicate");
    
    bst_delete(bst, 100); 

    assert_int_equal(bst->size, 2, "BST size after deleting non-existent value");
}

int main() {
    printf("Testing BST insert and find:\n");
    test_bst_insert_and_find();
    
    printf("\nTesting BST min and max:\n");
    test_bst_min_max();
    
    printf("\nTesting BST delete:\n");
    test_bst_delete();
    
    printf("\nTesting BST edge cases:\n");
    test_bst_edge_cases();
    
    return 0;
}
