#include <stdio.h>
#include <omp.h>
#include <time.h>

int main(void)
{
    int num_threads;

    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    // Sequential execution
    clock_t start = clock();
    printf("Sequential execution:\n");
    for (int i = 0; i < num_threads; i++)
    {
        printf("Hello, world.\n");
    }
    clock_t end = clock();
    double sequential_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Sequential Execution time: %f seconds\n", sequential_time);

    // Parallel execution
    omp_set_num_threads(num_threads);
    start = clock();
    printf("Parallel execution:\n");
#pragma omp parallel
    {
        printf("Hello, world from thread %d.\n", omp_get_thread_num());
    }
    end = clock();
    double parallel_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Parallel Execution time: %f seconds\n", parallel_time);

    // Calculating speedup
    if (parallel_time > 0) 
    {
        double speedup = sequential_time / parallel_time;
        printf("Speedup: %f\n", speedup);
    }
    else
    {
        printf("Parallel execution time is too small to calculate speedup.\n");
    }

    return 0;
}
