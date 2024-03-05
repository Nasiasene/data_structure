#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next; // Ponteiro para o próximo nó
    struct Node* jump; // Ponteiro para o próximo nó de salto
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->jump = NULL;
    return newNode;
}

void insert(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Função para definir os ponteiros de salto na lista
void setJumpPointers(Node* head, int jumpSize) {
    Node* current = head;
    while (current != NULL) {
        // Defina o ponteiro de salto para o próximo nó após "jumpSize" nós
        Node* jumpTarget = current;
        for (int i = 0; i < jumpSize && jumpTarget != NULL; i++) {
            jumpTarget = jumpTarget->next;
        }
        current->jump = jumpTarget;
        current = current->next;
    }
}

// Função para percorrer a lista usando os ponteiros de salto
void traverseWithJump(Node* head) {
    printf("Traversal with jumps: ");
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->jump;
    }
    printf("\n");
}

int main() {
    Node* head = NULL;
    insert(&head, 1);
    insert(&head, 2);
    insert(&head, 3);
    insert(&head, 4);
    insert(&head, 5);
    
    // Definindo os ponteiros de salto com um salto de tamanho 2
    setJumpPointers(head, 2);

    // Percorrendo a lista usando os ponteiros de salto
    traverseWithJump(head);

    return 0;
}