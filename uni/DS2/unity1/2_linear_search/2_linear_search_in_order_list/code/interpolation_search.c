#include <stdio.h>

int interpolationSearch(int array[], int len, int target) {
    int left = 0, right = len - 1;

    while (left <= right && target >= array[left] && target <= array[right]) {
        if (left == right) {
            if (array[left] == target)
                return left;
            return -1;
        }

        int pos = left + ((double)(right - left) / (array[right] - array[left])) * (target - array[left]);

        if (array[pos] == target)
            return pos;
        if (array[pos] < target)
            left = pos + 1;
        else
            right = pos - 1;
    }

    return -1; 
}

int main() {
    int array[] = {11, 12, 14, 25, 34, 64, 90};
    int target = 14;
    int size = sizeof(array) / sizeof(array[0]);
    int result = interpolationSearch(array, size, target);

    if (result == -1)
        printf("Elemento não encontrado no array\n");
    else
        printf("Elemento encontrado na posição: %d\n", result);

    return 0;
}
