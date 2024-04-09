#include <stdio.h>
#include "b_tree.h"

int main() {
    Node *root = create_node();

    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 5);
    insert(&root, 6);
    insert(&root, 12);
    insert(&root, 30);
    insert(&root, 7);

    printf("Traversal of the constructed B tree:\n");
    traverse(root);
    printf("\n");

    int key = 6;
    if (search(root, key)) {
        printf("Key %d found.\n", key);
    } else {
        printf("Key %d not found.\n", key);
    }

    key = 15;
    if (search(root, key)) {
        printf("Key %d found.\n", key);
    } else {
        printf("Key %d not found.\n", key);
    }

    return 0;
}
