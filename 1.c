#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int* genRandArray(int size, int maxValue) {
    int* arr = (int*)malloc((size + 1) * sizeof(int));
    if (arr == NULL) {
        printf("Ошибка выделения памяти");
    }

    arr[0] = size;

    srand(time(NULL));

    for (int i = 1; i <= size; i++) {
        arr[i] = rand() % (maxValue + 1);
    }

    return arr;
}

void print(int* arr) {
    int size = arr[0];
    printf("%d: ", size);
    for (int i = 1; i <= size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
}

int main(){
    srand(time(NULL));
    int size = rand() % 10;
    int maxValue = 100;

    int* arr = genRandArray(size,maxValue);
    print(arr);

    return 0;
}