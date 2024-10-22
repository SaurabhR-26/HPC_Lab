#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void initialize_matrix(int **matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            matrix[i][j] = rand() % 10;
        }
    }
}

void add_matrices(int **A, int **B, int **C, int size, int threads)
{
#pragma omp parallel for num_threads(threads)
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

int **allocate_matrix(int size)
{
    int **matrix = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++)
    {
        matrix[i] = (int *)malloc(size * sizeof(int));
    }
    return matrix;
}

void free_matrix(int **matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

int main()
{
    int sizes[] = {250, 500, 750, 1000, 2000};
    int num_sizes = 5;
    int num_threads[] = {1, 2, 4, 8};
    int num_thread_sizes = 4;
    double start_time, end_time;

    for (int s = 0; s < num_sizes; s++)
    {
        int size = sizes[s];
        printf("Matrix Size: %d x %d\n", size, size);

        int **A = allocate_matrix(size);
        int **B = allocate_matrix(size);
        int **C = allocate_matrix(size);

        initialize_matrix(A, size);
        initialize_matrix(B, size);

        for (int t = 0; t < num_thread_sizes; t++)
        {
            int threads = num_threads[t];
            printf("Number of Threads: %d\n", threads);

            start_time = omp_get_wtime();
            add_matrices(A, B, C, size, threads);
            end_time = omp_get_wtime();

            printf("Time taken: %f seconds\n", end_time - start_time);
        }

        free_matrix(A, size);
        free_matrix(B, size);
        free_matrix(C, size);

        printf("\n");
    }

    return 0;
}
