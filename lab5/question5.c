#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define BLOCK_SIZE 64

void matrixMultiplySerial(int n, int **A, int **B, int **C)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void matrixMultiplyParallel(int n, int **A, int **B, int **C)
{
#pragma omp parallel
    {
#pragma omp for collapse(2) schedule(dynamic, 1)
        for (int ii = 0; ii < n; ii += BLOCK_SIZE)
        {
            for (int jj = 0; jj < n; jj += BLOCK_SIZE)
            {
                for (int kk = 0; kk < n; kk += BLOCK_SIZE)
                {
                    for (int i = ii; i < ii + BLOCK_SIZE && i < n; i++)
                    {
                        for (int j = jj; j < jj + BLOCK_SIZE && j < n; j++)
                        {
                            int sum = 0;
                            for (int k = kk; k < kk + BLOCK_SIZE && k < n; k++)
                            {
                                sum += A[i][k] * B[k][j];
                            }
#pragma omp atomic
                            C[i][j] += sum;
                        }
                    }
                }
            }
        }
    }
}

int main()
{
    int n = 1500;
    int **A, **B, **C, **C_serial;

    A = malloc(n * sizeof(int *));
    B = malloc(n * sizeof(int *));
    C = malloc(n * sizeof(int *));
    C_serial = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        A[i] = malloc(n * sizeof(int));
        B[i] = malloc(n * sizeof(int));
        C[i] = malloc(n * sizeof(int));
        C_serial[i] = malloc(n * sizeof(int));
    }

// matrix initialization
#pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            A[i][j] = rand() % 100;
            B[i][j] = rand() % 100;
            C[i][j] = 0;
            C_serial[i][j] = 0;
        }
    }

    // Serial
    double start = omp_get_wtime();
    matrixMultiplySerial(n, A, B, C_serial);
    double end = omp_get_wtime();
    printf("Serial execution time: %lf seconds\n", end - start);

    // Parallel
    start = omp_get_wtime();
    matrixMultiplyParallel(n, A, B, C);
    end = omp_get_wtime();
    printf("Parallel execution time: %lf seconds\n", end - start);

    // verification of results
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (C[i][j] != C_serial[i][j])
            {
                printf("Error: Results do not match at (%d, %d)\n", i, j);
                return 1;
            }
        }
    }
    printf("Results verified: Parallel and serial outputs match.\n");

    // Cleanup
    for (int i = 0; i < n; i++)
    {
        free(A[i]);
        free(B[i]);
        free(C[i]);
        free(C_serial[i]);
    }
    free(A);
    free(B);
    free(C);
    free(C_serial);

    return 0;
}