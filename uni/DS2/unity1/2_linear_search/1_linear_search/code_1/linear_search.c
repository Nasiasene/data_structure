#include <stdio.h>

int sequential_search(int array[], int key, int length) {
    for (int i = 0; i < length; i++) {
        if (array[i] == key) {
            return i;
        }
    }
    return -1;
}

int main() {
    int array[] = {12, 45, 78, 23, 56};
    int target = 10;
    int size = sizeof(array) / sizeof(array[0]);

    int index = sequential_search(array, target, size);

    if (index != -1) {
        printf("Elemento encontrado na posição %d.\n", index);
    } else {
        printf("Elemento não encontrado.\n");
    }

    return 0;
}