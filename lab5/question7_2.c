#include <stdio.h>
#include <omp.h>

#define N 1000

int main() {
    int i;
    int array[N];
    int total_sum = 0;

    for (i = 0; i < N; i++) {
        array[i] = 1;  
    }

    #pragma omp parallel
    {
        int local_sum = 0;

        #pragma omp for
        for (i = 0; i < N; i++) {
            local_sum += array[i];
        }

        #pragma omp critical
        {
            total_sum += local_sum;
        }
    }

    printf("Total sum: %d\n", total_sum);
    return 0;
}
