#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define NUM_POINTS 100000000

double calculate_pi_sequential(long long num_points) {
    long long inside_circle = 0;
    unsigned int seed = time(NULL);

    for (long long i = 0; i < num_points; i++) {
        double x = (double)rand_r(&seed) / RAND_MAX;
        double y = (double)rand_r(&seed) / RAND_MAX;
        if (x*x + y*y <= 1.0) {
            inside_circle++;
        }
    }

    return 4.0 * inside_circle / num_points;
}

double calculate_pi_parallel(long long num_points) {
    long long inside_circle = 0;

    #pragma omp parallel
    {
        unsigned int seed = omp_get_thread_num();
        #pragma omp for reduction(+:inside_circle)
        for (long long i = 0; i < num_points; i++) {
            double x = (double)rand_r(&seed) / RAND_MAX;
            double y = (double)rand_r(&seed) / RAND_MAX;
            if (x*x + y*y <= 1.0) {
                inside_circle++;
            }
        }
    }

    return 4.0 * inside_circle / num_points;
}

int main() {
    double start_time, end_time, pi;

    // Sequential calculation
    start_time = omp_get_wtime();
    pi = calculate_pi_sequential(NUM_POINTS);
    end_time = omp_get_wtime();
    printf("Sequential Pi: %.10f\n", pi);
    printf("Sequential Time: %.6f seconds\n", end_time - start_time);

    // Parallel calculation
    start_time = omp_get_wtime();
    pi = calculate_pi_parallel(NUM_POINTS);
    end_time = omp_get_wtime();
    printf("Parallel Pi: %.10f\n", pi);
    printf("Parallel Time: %.6f seconds\n", end_time - start_time);

    return 0;
}