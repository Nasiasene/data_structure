#include <stdio.h>
#include <stdlib.h>
#include "b_tree.h"

Node *create_node() {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    new_node->num_keys = 0;
    new_node->is_leaf = 1;
    return new_node;
}

void split_child(Node *parent, int index) {
    Node *new_node = create_node();
    Node *child = parent->children[index];
    new_node->is_leaf = child->is_leaf;
    new_node->num_keys = MAX_KEYS / 2;

    for (int i = 0; i < MAX_KEYS / 2; ++i) {
        new_node->keys[i] = child->keys[i + MAX_KEYS / 2];
    }

    if (!child->is_leaf) {
        for (int i = 0; i < MAX_KEYS / 2 + 1; ++i) {
            new_node->children[i] = child->children[i + MAX_KEYS / 2];
        }
    }

    child->num_keys = MAX_KEYS / 2;
    parent->num_keys++;

    for (int i = parent->num_keys; i > index + 1; --i) {
        parent->children[i] = parent->children[i - 1];
    }

    parent->children[index + 1] = new_node;

    for (int i = parent->num_keys - 1; i > index; --i) {
        parent->keys[i] = parent->keys[i - 1];
    }

    parent->keys[index] = child->keys[MAX_KEYS / 2 - 1];
}

void insert_non_full(Node *node, int key) {
    int i = node->num_keys - 1;
    if (node->is_leaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->num_keys++;
    } else {
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;
        if (node->children[i]->num_keys == MAX_KEYS) {
            split_child(node, i);
            if (key > node->keys[i]) {
                i++;
            }
        }
        insert_non_full(node->children[i], key);
    }
}

void insert(Node **root, int key) {
    if ((*root)->num_keys == MAX_KEYS) {
        Node *new_root = create_node();
        new_root->is_leaf = 0;
        new_root->children[0] = *root;
        *root = new_root;
        split_child(new_root, 0);
    }
    insert_non_full(*root, key);
}

void traverse(Node *root) {
    if (root != NULL) {
        for (int i = 0; i < root->num_keys; ++i) {
            traverse(root->children[i]);
            printf("%d ", root->keys[i]);
        }
        traverse(root->children[root->num_keys]);
    }
}

int search(Node *root, int key) {
    int i = 0;
    while (i < root->num_keys && key > root->keys[i]) {
        i++;
    }
    if (root->keys[i] == key) {
        printf("Key %d found.\n", key);
        return 1;
    }
    if (root->is_leaf) {
        printf("Key %d not found.\n", key);
        return 0;
    }
    return search(root->children[i], key);
}
