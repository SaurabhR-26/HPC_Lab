#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int compareAsc(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int compareDesc(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

int main() {
    int n;
    printf("Enter the size of the vectors: ");
    scanf("%d", &n);

    srand(time(0));

    int vector1[n], vector2[n];

    for (int i = 0; i < n; i++) {
        vector1[i] = rand() % 1000 + 1;  
        vector2[i] = rand() % 1000 + 1;  
    }

    qsort(vector1, n, sizeof(int), compareAsc);
    qsort(vector2, n, sizeof(int), compareDesc);


    long long int minScalarProduct = 0;

    // Sequential execution
    double start_time_seq = omp_get_wtime();
    for (int i = 0; i < n; i++) {
        minScalarProduct += (long long int)(vector1[i] * vector2[i]);
    }
    double end_time_seq = omp_get_wtime();
    double time_seq = end_time_seq - start_time_seq;

    printf("The minimum scalar product (sequential) is: %lld\n", minScalarProduct);
    printf("Time taken for sequential execution: %f seconds\n", time_seq);


    minScalarProduct = 0;

    // Parallel execution
    double start_time_par = omp_get_wtime();
    #pragma omp parallel for reduction(+:minScalarProduct) schedule(static)
    for (int i = 0; i < n; i++) {
        minScalarProduct += (long long int)(vector1[i] * vector2[i]);
    }

    double end_time_par = omp_get_wtime();
    double time_par = end_time_par - start_time_par;

    printf("The minimum scalar product (parallel) is: %lld\n", minScalarProduct);
    printf("Time taken for parallel execution: %f seconds\n", time_par);

    return 0;
}
