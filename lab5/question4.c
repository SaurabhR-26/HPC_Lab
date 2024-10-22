#include <stdio.h>
#include <omp.h>

int main() {
    int total_sum;
    int partial_sum;
    int num_threads = 4;  

    #pragma omp parallel num_threads(num_threads) private(partial_sum)
    {
        int tid = omp_get_thread_num();
        int n_per_thread = 20 / num_threads;  
        int start = tid * n_per_thread + 1;   
        int end = start + n_per_thread - 1;   

        partial_sum = 0;

        for (int i = start; i <= end; i++) {
            partial_sum += i;
        }

        #pragma omp atomic
        total_sum+=partial_sum;

        printf("Thread ID: %d, Partial Sum: %d\n", tid, partial_sum);
    }

    printf("Final Total Sum (from the last thread): %d\n", total_sum);

    return 0;
}
