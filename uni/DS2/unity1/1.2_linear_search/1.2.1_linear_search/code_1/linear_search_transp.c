#include <stdio.h>

void linearSearchWithTransposition(int arr[], int len, int key) {
    for (int i = 0; i < len; i++) {
        if (arr[i] == key) {
            if (i > 0) {
                int j = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = j;
                printf("Elemento %d encontrado e transposto com o anterior.\n", key);
            } else {
                printf("Elemento %d encontrado no início do array.\n", key);
            }
            return;
        }
    }
    printf("Elemento %d não encontrado no array.\n", key);
}

int main() {
    int arr[] = {12, 45, 78, 23, 56};
    int target = 78;
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Array antes da busca e transposição:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    linearSearchWithTransposition(arr, size, target);
    printf("Array após a busca e transposição:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}