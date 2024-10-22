#include <stdio.h>
#include <omp.h>

int fibonacci(int n)
{
    if (n <= 1)
    {
        return n;
    }

    int x, y;

#pragma omp task shared(x) if (n > 10)
    x = fibonacci(n - 1);

#pragma omp task shared(y) if (n > 10)
    y = fibonacci(n - 2);

#pragma omp taskwait
    return x + y;
}

int main()
{
    int n;
    int fib;
    double start_time, end_time;

    printf("Enter number: ");
    scanf("%d", &n);

    start_time = omp_get_wtime();

#pragma omp parallel
    {
#pragma omp single
        {
            fib = fibonacci(n);
        }
    }

    end_time = omp_get_wtime();

    printf("Fibonacci of %d is %d\n", n, fib);
    printf("Time taken: %f seconds\n", end_time - start_time);

    return 0;
}
