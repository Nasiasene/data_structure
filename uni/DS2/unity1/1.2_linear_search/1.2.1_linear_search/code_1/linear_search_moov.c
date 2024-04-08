#include <stdio.h>

void linearSearchWithMove(int arr[], int len, int key) {
    for (int i = 0; i < len; i++) {
        if (arr[i] == key) {
            int k = arr[i];
            for (int j = i; j > 0; j--) {
                arr[j] = arr[j - 1];
            }
            arr[0] = k;
            printf("Elemento %d encontrado e movido para o início do array.\n", key);
            return;
        }
    }
    printf("Elemento %d não encontrado no array.\n", key);
}

int main() {
    int arr[] = {12, 45, 78, 23, 56};
    int target = 78;
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Array antes da busca e movimentação:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    linearSearchWithMove(arr, size, target);
    printf("\nArray após a busca e movimentação:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}