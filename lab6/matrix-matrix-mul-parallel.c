#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 500

void matrixMultiply(int n, int A[n][n], int B[n][n], int C[n][n])
{
    #pragma omp parallel for collapse(2) schedule(static)
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int sum = 0;
            for (int k = 0; k < n; k++)
            {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
}

int main()
{
    int n = SIZE;
    int (*A)[n] = malloc(sizeof(int[n][n]));
    int (*B)[n] = malloc(sizeof(int[n][n]));
    int (*C)[n] = malloc(sizeof(int[n][n]));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }

    double start = omp_get_wtime();
    matrixMultiply(n, A, B, C);
    double end = omp_get_wtime();

    printf("Parallel Program Time: %f\n", end - start);
    printf("Matrix multiplication (parallel) using OpenMP completed.\n");

    free(A);
    free(B);
    free(C);

    return 0;
}