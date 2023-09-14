#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **genRandMatrix(int size, int maxValue)
{
    int **matrix = (int **)malloc((size + 1) * sizeof(int *)); // Увеличил на 1 для хранения размера матрицы
    if (matrix == NULL)
    {
        printf("Ошибка выделения памяти для указателей на строки матрицы\n");
        return NULL;
    }

    for (int i = 0; i < size; i++)
    {
        int matrixSize = rand() % maxValue + 1;
        matrix[i] = (int *)malloc((matrixSize + 1) * sizeof(int)); // Увеличил на 1 для хранения размера строки
        if (matrix[i] == NULL)
        {
            printf("Ошибка выделения памяти для строки матрицы %d\n", i);
            return NULL;
        }
        matrix[i][0] = matrixSize; // Сохраняем размер строки в первом элементе
        for (int j = 1; j <= matrixSize; j++)
        {
            matrix[i][j] = rand() % 10;
        }
    }

    matrix[size] = NULL; // Последний указатель устанавливаем в NULL

    return matrix;
}

void printMatrix(int **matrix)
{
    int i = 0;
    while (matrix[i] != NULL)
    {                                  // Проверяем, что указатель на строку не равен NULL
        int matrixSize = matrix[i][0]; // Получаем размер строки
        if (matrixSize <= 0)
        {
            continue;
        }

        printf("%d: ", matrixSize); // Выводим количество чисел в строке
        for (int j = 1; j <= matrixSize; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
        i++;
    }
}

int main()
{
    srand(time(NULL));

    int size = rand() % 10;
    int maxValue = 10;
    int **matrix = genRandMatrix(size, maxValue);
    printf("%d\n", size);

    printMatrix(matrix);

    free(matrix);

    return 0;
}
