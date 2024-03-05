#include <stdio.h>
#include <stdlib.h>

// Definição de um nó na árvore
typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

// Função auxiliar para criar um novo nó
Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

// Função para realizar a operação de rotação à direita
Node* rightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

// Função para realizar a operação de rotação à esquerda
Node* leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

// Função para realizar a operação de splay em um nó com a chave k
Node* splay(Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    // Caso o nó esteja à esquerda da raiz
    if (root->key > key) {
        // Caso o nó não esteja presente na árvore
        if (root->left == NULL)
            return root;

        // Zig-zig (Rotação à direita duas vezes)
        if (root->left->key > key) {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        }
        // Zig-zag (Rotação à esquerda seguida de rotação à direita)
        else if (root->left->key < key) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }

        // Rotação à direita, se necessário
        return (root->left == NULL) ? root : rightRotate(root);
    }
    // Caso o nó esteja à direita da raiz
    else {
        // Caso o nó não esteja presente na árvore
        if (root->right == NULL)
            return root;

        // Zig-zag (Rotação à direita seguida de rotação à esquerda)
        if (root->right->key > key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        }
        // Zig-zig (Rotação à esquerda duas vezes)
        else if (root->right->key < key) {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }

        // Rotação à esquerda, se necessário
        return (root->right == NULL) ? root : leftRotate(root);
    }
}

// Função para inserir uma nova chave na árvore
Node* insert(Node* root, int key) {
    // Caso a árvore esteja vazia ou a chave já exista
    if (root == NULL || root->key == key)
        return root;

    // Splay para trazer o último nó acessado para a raiz
    root = splay(root, key);

    // Criar um novo nó
    Node* newNode = newNode->key;

    // Caso a chave seja menor que a raiz, fazer o novo nó como filho esquerdo
    if (root->key > key) {
        newNode->right = root;
        newNode->left = root->left;
        root->left = NULL;
    }
    // Caso a chave seja maior que a raiz, fazer o novo nó como filho direito
    else {
        newNode->left = root;
        newNode->right = root->right;
        root->right = NULL;
    }

    // A nova raiz será o novo nó
    return newNode;
}

// Função para realizar uma busca na árvore
Node* search(Node* root, int key) {
    return splay(root, key);
}

// Função para realizar uma remoção na árvore
Node* delete(Node* root, int key) {
    if (root == NULL)
        return root;

    root = splay(root, key);

    if (root->key != key)
        return root;

    Node* temp;

    if (root->left == NULL) {
        temp = root;
        root = root->right;
    } else {
        temp = root;

        root = splay(root->left, key);
        root->right = temp->right;
    }

    free(temp);
    return root;
}

// Função para percorrer a árvore em ordem
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

// Função principal
int main() {
    Node* root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    printf("Árvore em ordem: ");
    inorder(root);
    printf("\n");

    root = search(root, 20);
    printf("Após buscar o elemento 20, a árvore em ordem: ");
    inorder(root);
    printf("\n");

    root = delete(root, 30);
    printf("Após remover o elemento 30, a árvore em ordem: ");
    inorder(root);
    printf("\n");

    return 0;
}
