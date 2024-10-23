#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include "data_structure.h" 

void print_list(list_t *list) {
    node_t *current = list->head;
    printf("List: ");
    while (current != NULL) {
        printf("%zu ", *(current->val));
        current = current->next;
    }
    printf("\n");
}

void assert_equal(const char *test_desc, size_t actual, size_t expected) {
    if (actual != expected) {
        printf("Test Failed: %s\n", test_desc);
        printf("  Expected: %d\n", (int)expected);
        printf("  Actual:   %d\n", (int)actual);
    } else {
        printf("Test Passed: %s\n", test_desc);
    }
}

void assert_ptr_equal(const char *test_desc, void *actual, void *expected) {
    if (actual != expected) {
        printf("Test Failed: %s\n", test_desc);
        printf("  Expected: %p\n", expected);
        printf("  Actual:   %p\n", actual);
    } else {
        printf("Test Passed: %s\n", test_desc);
    }
}

int main() {
    list_t *list = list_new();
    assert_ptr_equal("New List Head should be NULL", list->head, NULL);
    assert_ptr_equal("New List Tail should be NULL", list->tail, NULL);
    assert_equal("New List Size should be 0", list->size, 0);

    size_t val1 = 1, val2 = 2, val3 = 3, val4 = 4;
    list_add_front(list, &val1); 
    list_add_back(list, &val2); 

    assert_equal("List Size after 2 additions", list->size, 2);
    assert_ptr_equal("List Head value after adding 1 at front", list->head->val, &val1);
    assert_ptr_equal("List Tail value after adding 2 at back", list->tail->val, &val2);

    list_add(list, &val1, &val3);  
    assert_equal("List Size after adding 3 after 1", list->size, 3);
    assert_ptr_equal("Value after 1 should be 3", list->head->next->val, &val3);
    assert_ptr_equal("Value after 3 should be 2", list->head->next->next->val, &val2);

    list_add(list, &val2, &val4); 
    assert_equal("List Size after adding 4 after 2", list->size, 4);
    assert_ptr_equal("Tail value should now be 4", list->tail->val, &val4);

    size_t *deleted = list_delete_front(list);
    assert_ptr_equal("Deleted value from front", deleted, &val1);
    assert_equal("List Size after deleting front", list->size, 3);

    deleted = list_delete_back(list); 
    assert_ptr_equal("Deleted value from back", deleted, &val4);
    assert_equal("List Size after deleting back", list->size, 2);

    deleted = list_delete(list, &val3);
    assert_ptr_equal("Deleted specific value", deleted, &val3);
    assert_equal("List Size after deleting specific element", list->size, 1);

    list_add_front(list, &val1);
    list_add_back(list, &val2);
    list_add(list, &val1, &val3);

    node_t *found_node = node_find(list, &val2);
    assert_ptr_equal("Find node with value 2", found_node->val, &val2);

    found_node = node_find(list, &val3);
    assert_ptr_equal("Find node with value 3", found_node->val, &val3);

    found_node = node_find(list, &val1);
    assert_ptr_equal("Find node with value 1", found_node->val, &val1);

    size_t non_existent_val = 100;
    found_node = node_find(list, &non_existent_val);
    assert_ptr_equal("Find non-existent node", found_node, NULL);

    printf("All tests completed.\n");
    return 0;
}
