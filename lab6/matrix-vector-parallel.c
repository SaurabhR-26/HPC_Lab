#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 10000 // Size of the matrix (N x N) and vector (N)

void matrixVectorMultiply(int n, double A[n][n], double x[n], double y[n])
{
    #pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        y[i] = 0.0;
        for (int j = 0; j < n; j++)
        {
            y[i] += A[i][j] * x[j];
        }
    }
}

int main()
{
    int n = SIZE;
    double (*A)[n] = malloc(sizeof(double[n][n]));
    double *x = malloc(sizeof(double[n]));
    double *y = malloc(sizeof(double[n]));

    #pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        x[i] = (double)rand() / RAND_MAX;
        for (int j = 0; j < n; j++)
        {
            A[i][j] = (double)rand() / RAND_MAX;
        }
    }

    double start = omp_get_wtime();
    matrixVectorMultiply(n, A, x, y);
    double end = omp_get_wtime();

    printf("Parallel Program Time: %f seconds\n", end - start);
    printf("Matrix-vector multiplication (parallel) using OpenMP completed.\n");

    free(A);
    free(x);
    free(y);

    return 0;
}