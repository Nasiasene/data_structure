#include <iostream>

struct TreeNode {
    int data;
    // ponteiroa para seus filhos.
    TreeNode* left; 
    TreeNode* right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {} // um objeto quando instaciando deverá passar o valor inteiro para arvore
};

class BinaryTree {
    TreeNode* root;

    TreeNode* insertRec(TreeNode* node, int val);
    void inorderTraversal(TreeNode* node);

public:
    BinaryTree() : root(nullptr) {}

    void insert(int val) {
        root = insertRec(root, val);
    }

    void inorderTraversal() {
        inorderTraversal(root);
    }
};

TreeNode* BinaryTree::insertRec(TreeNode* node, int val) {
    if (node == nullptr) {
        return new TreeNode(val);
    }

    if (val < node->data) {
        node->left = insertRec(node->left, val);
    } else if (val > node->data) {
        node->right = insertRec(node->right, val);
    }

    return node;
}

void BinaryTree::inorderTraversal(TreeNode* node) {
    if (node == nullptr) {
        return;
    }

    inorderTraversal(node->left);
    std::cout << node->data << " ";
    inorderTraversal(node->right);
}


int main() {
    BinaryTree tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(70);
    tree.insert(60);
    tree.insert(80);

    std::cout << "Inorder Traversal: ";
    tree.inorderTraversal();
    std::cout << std::endl;

    return 0;
}
