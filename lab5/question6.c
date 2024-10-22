#include <stdio.h>
#include <omp.h>

void printSeries(int start, int step, int count) {
    for (int i = 0; i < count; i++) {
        printf("%d ", start + i * step);
    }
    printf("\n");
}

int main() {
    int count = 10;

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            printf("Series of 2: ");
            printSeries(2, 2, count);
        }

        #pragma omp section
        {
            printf("Series of 4: ");
            printSeries(4, 4, count);
        }
    }

    return 0;
}
