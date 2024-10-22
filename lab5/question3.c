#include <stdio.h>
#include <omp.h>

int main() {
    int num_threads = 4; 
    int Aryabhatta = 11;
    #pragma omp parallel num_threads(num_threads) private(Aryabhatta)
    {
        Aryabhatta = 10;
        int tid = omp_get_thread_num();

        int result = tid * Aryabhatta;

        printf("Thread ID: %d, Result of Thread ID * Aryabhatta: %d\n", tid, result);
    }
    return 0;
}
