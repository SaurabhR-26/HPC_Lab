#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void vector_scalar_addition_sequential(double *vector, double scalar, int size)
{
    for (int i = 0; i < size; i++)
    {
        vector[i] += scalar;
    }
}

void vector_scalar_addition_parallel(double *vector, double scalar, int size, int num_threads)
{
#pragma omp parallel for num_threads(num_threads)
    for (int i = 0; i < size; i++)
    {
        vector[i] += scalar;
    }
}

int main()
{
    int size = 1000000;
    double scalar = 5.0;
    int num_threads[] = {1, 2, 4, 8};

    double *arr = (double *)malloc(size * sizeof(double));
    double *arr_copy = (double *)malloc(size * sizeof(double));

    for (int i = 0; i < size; i++)
    {
        arr[i] = (double)i;
        arr_copy[i] = (double)i;
    }

    // Sequential execution
    double start_time = omp_get_wtime();
    vector_scalar_addition_sequential(arr, scalar, size);
    double end_time = omp_get_wtime();
    printf("Sequential execution time: %f seconds\n", end_time - start_time);

    // Parallel execution
    for (int i = 0; i < sizeof(num_threads) / sizeof(num_threads[0]); i++)
    {
        // Reset arr to original values
        for (int j = 0; j < size; j++)
        {
            arr[j] = arr_copy[j];
        }

        start_time = omp_get_wtime();
        vector_scalar_addition_parallel(arr, scalar, size, num_threads[i]);
        end_time = omp_get_wtime();

        printf("Parallel execution - Threads: %d, Time taken: %f seconds\n", num_threads[i], end_time - start_time);
    }

    free(arr);
    free(arr_copy);
    return 0;
}