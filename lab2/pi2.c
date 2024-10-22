#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main() {
    long long int num_iterations = 1000000000;  // Number of random points
    long long int inside_circle = 0;
    double x, y;
    double pi;
    
    srand(time(NULL));

    #pragma omp parallel
    {
        unsigned int seed = time(NULL) ^ omp_get_thread_num();
        #pragma omp for reduction(+:inside_circle)
        for (long long int i = 0; i < num_iterations; i++) {
            x = (double)rand_r(&seed) / RAND_MAX;
            y = (double)rand_r(&seed) / RAND_MAX;
            if (x * x + y * y <= 1) {
                inside_circle++;
            }
        }
    }
    
    pi = (double)inside_circle / num_iterations * 4;
    printf("Parallel Pi: %f\n", pi);
    
    return 0;
}
