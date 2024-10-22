#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

#define VECTOR_SIZE 200
#define SCALAR 5

void initialize_vector(float *vector, int size) {
    for (int i = 0; i < size; i++) {
        vector[i] = rand() % 100; 
    }
}

void print_vector(float *vector, int size) {
    for (int i = 0; i < size; i++) {
        printf("%.2f ", vector[i]);
        if ((i + 1) % 10 == 0) printf("\n");
    }
}

void scalar_addition_static(float *vector, float scalar, int size, int chunk_size) {
    #pragma omp parallel for schedule(static, chunk_size) 
    for (int i = 0; i < size; i++) {
        vector[i] += scalar;
    }
}

void scalar_addition_dynamic(float *vector, float scalar, int size, int chunk_size) {
    #pragma omp parallel for schedule(dynamic, chunk_size) 
    for (int i = 0; i < size; i++) {
        vector[i] += scalar;
    }
}

void scalar_addition_nowait(float *vector, float scalar, int size) {
    #pragma omp parallel 
    {
        #pragma omp for nowait
        for (int i = 0; i < size; i++) {
            vector[i] += scalar;
        }
        
        // Some independent computation
        #pragma omp single nowait
        printf("This is an independent task, executed by thread %d\n", omp_get_thread_num());
    }
}

int main() {
    float vector[VECTOR_SIZE];
    initialize_vector(vector, VECTOR_SIZE);

    printf("Original Vector:\n");
    print_vector(vector, VECTOR_SIZE);

    int chunk_size;

    printf("\n--- Static Scheduling ---\n");
    for (chunk_size = 1; chunk_size <= 100; chunk_size *= 10) {
        double start_time = omp_get_wtime();
        scalar_addition_static(vector, SCALAR, VECTOR_SIZE, chunk_size);
        double end_time = omp_get_wtime();
        printf("Chunk size %d - Time: %f seconds\n", chunk_size, end_time - start_time);
    }

    printf("\n--- Dynamic Scheduling ---\n");
    initialize_vector(vector, VECTOR_SIZE);
    for (chunk_size = 1; chunk_size <= 100; chunk_size *= 10) {
        double start_time = omp_get_wtime();
        scalar_addition_dynamic(vector, SCALAR, VECTOR_SIZE, chunk_size);
        double end_time = omp_get_wtime();
        printf("Chunk size %d - Time: %f seconds\n", chunk_size, end_time - start_time);
    }

    printf("\n--- Nowait Clause ---\n");
    initialize_vector(vector, VECTOR_SIZE);
    double start_time = omp_get_wtime();
    scalar_addition_nowait(vector, SCALAR, VECTOR_SIZE);
    double end_time = omp_get_wtime();
    printf("Time with nowait: %f seconds\n", end_time - start_time);

    return 0;
}
