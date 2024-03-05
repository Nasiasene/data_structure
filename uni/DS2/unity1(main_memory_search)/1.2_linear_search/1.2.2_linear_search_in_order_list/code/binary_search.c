#include <stdio.h>

int binarySearch(int array[], int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        // Verifica se o elemento está presente no meio
        if (array[mid] == target)
            return mid;
        // Se o elemento estiver na metade esquerda
        if (array[mid] < target)
            left = mid + 1;
        // Se o elemento estiver na metade direita
        else
            right = mid - 1;
    }

    return -1;
}

int main() {
    int array[] = {11, 12, 14, 25, 34, 64, 90};
    int target = 14;
    int size = sizeof(array) / sizeof(array[0]);
    int result = binarySearch(array, 0, size - 1, target);

    if (result == -1)
        printf("Elemento não encontrado no array\n");
    else
        printf("Elemento encontrado na posição: %d\n", result);

    return 0;
}
