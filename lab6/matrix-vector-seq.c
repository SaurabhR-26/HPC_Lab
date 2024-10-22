#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10000 // Size of the matrix (N x N) and vector (N)

void matrixVectorMultiply(int n, double A[n][n], double x[n], double y[n])
{
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

    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        x[i] = (double)rand() / RAND_MAX;
        for (int j = 0; j < n; j++)
        {
            A[i][j] = (double)rand() / RAND_MAX;
        }
    }

    clock_t start = clock();
    matrixVectorMultiply(n, A, x, y);
    clock_t end = clock();

    printf("Sequential Program Time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    printf("Matrix-vector multiplication completed.\n");

    free(A);
    free(x);
    free(y);

    return 0;
}