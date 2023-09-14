#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **genRandMatrix(int size, int maxValue)
{
    int **matrix = (int **)malloc((size + 1) * sizeof(int *)); // �������� �� 1 ��� �������� ������� �������
    if (matrix == NULL)
    {
        printf("������ ��������� ������ ��� ���������� �� ������ �������\n");
        return NULL;
    }

    for (int i = 0; i < size; i++)
    {
        int matrixSize = rand() % maxValue + 1;
        matrix[i] = (int *)malloc((matrixSize + 1) * sizeof(int)); // �������� �� 1 ��� �������� ������� ������
        if (matrix[i] == NULL)
        {
            printf("������ ��������� ������ ��� ������ ������� %d\n", i);
            return NULL;
        }
        matrix[i][0] = matrixSize; // ��������� ������ ������ � ������ ��������
        for (int j = 1; j <= matrixSize; j++)
        {
            matrix[i][j] = rand() % 10;
        }
    }

    matrix[size] = NULL; // ��������� ��������� ������������� � NULL

    return matrix;
}

void printMatrix(int **matrix)
{
    int i = 0;
    while (matrix[i] != NULL)
    {                                  // ���������, ��� ��������� �� ������ �� ����� NULL
        int matrixSize = matrix[i][0]; // �������� ������ ������
        if (matrixSize <= 0)
        {
            continue;
        }

        printf("%d: ", matrixSize); // ������� ���������� ����� � ������
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
