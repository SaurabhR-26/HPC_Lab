#include <stdio.h>
#include <omp.h>

int main() {
    int sum_of_squares = 0;
    int num_threads = 4;  

    
    #pragma omp parallel num_threads(num_threads) reduction(+:sum_of_squares)
    {
        int tid = omp_get_thread_num();
        int square = tid * tid;

        printf("Thread ID: %d, Square: %d\n", tid, square);

        sum_of_squares += square;
    }

    printf("Sum of squares of thread IDs: %d\n", sum_of_squares);

    return 0;
}
