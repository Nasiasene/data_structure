#include <iostream>

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    BinaryTree() : root(nullptr) {}

    void insert(int val, bool insertLeft = true) {
        if (root == nullptr) {
            root = new TreeNode(val);
        } else {
            insertRec(root, val, insertLeft);
        }
    }

    void inorderTraversal() {
        inorderTraversal(root);
    }

private:
    TreeNode* root;

    void insertRec(TreeNode* node, int val, bool insertLeft) {
        if (insertLeft) {
            if (node->left == nullptr) {
                node->left = new TreeNode(val);
            } else {
                insertRec(node->left, val, insertLeft);
            }
        } else {
            if (node->right == nullptr) {
                node->right = new TreeNode(val);
            } else {
                insertRec(node->right, val, insertLeft);
            }
        }
    }

    void inorderTraversal(TreeNode* node) {
        if (node == nullptr) {
            return;
        }

        inorderTraversal(node->left);
        std::cout << node->data << " ";
        inorderTraversal(node->right);
    }
};

int main() {
    BinaryTree tree;
    tree.insert(1); // Insere à esquerda por padrão
    tree.insert(2, false); // Insere à direita
    tree.insert(3);
    tree.insert(4, false);
    tree.insert(5);
    tree.insert(6, false);

    std::cout << "Inorder Traversal: ";
    tree.inorderTraversal();
    std::cout << std::endl;

    return 0;
}
