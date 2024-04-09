#ifndef B_TREE_H
#define B_TREE_H

#define MAX_KEYS 4

typedef struct node {
    int keys[MAX_KEYS];
    struct node *children[MAX_KEYS + 1];
    int num_keys;
    int is_leaf;
} Node;

Node *create_node();
void split_child(Node *parent, int index);
void insert_non_full(Node *node, int key);
void insert(Node **root, int key);
void traverse(Node *root);
int search(Node *root, int key);


#endif
