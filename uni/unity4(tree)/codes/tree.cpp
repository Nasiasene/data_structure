//árvore n-ária (uma árvore onde cada nó pode ter qualquer número de filhos)

#include <iostream>
#include <vector>

class TreeNode {
public:
    int data; // informação da folha
    std::vector<TreeNode*> children; //vetor de filhos.

    TreeNode(int val) : data(val) {} // um objeto do tipo folha recebrá como parâmetro na sua criação o seu valor.
};

class Tree {
public:
    TreeNode* root; //Ponteiro para raiz da árvore.

    Tree(int val) {
        root = new TreeNode(val); // raiz será passada como par6ametro ao criar um objeto desta classe.
    }

    void addChild(TreeNode* parent, int val) { // Adiciona um filho a um nó.
        TreeNode* child = new TreeNode(val);
        parent->children.push_back(child);
    }

    void printTree(TreeNode* node, int depth = 0) {
        if (node == nullptr) {
            return;
        }

        for (int i = 0; i < depth; i++) {
            std::cout << "  ";
        }

        std::cout << node->data << std::endl;

        for (TreeNode* child : node->children) {
            printTree(child, depth + 1);
        }
    }
};

int main() {
    Tree tree(1);

    TreeNode* node2 = tree.root;
    tree.addChild(node2, 2);
    tree.addChild(node2, 3);
    tree.addChild(node2, 4);

    TreeNode* node5 = node2->children[0];
    tree.addChild(node5, 5);
    tree.addChild(node5, 6);

    TreeNode* node7 = node2->children[1];
    tree.addChild(node7, 7);

    std::cout << "Arvore nao binaria:" << std::endl;
    tree.printTree(tree.root);

    return 0;
}
