#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    long long int num_iterations = 1000000000;  // Number of random points
    long long int inside_circle = 0;
    double x, y;
    double pi;
    
    srand(time(NULL));
    
    for (long long int i = 0; i < num_iterations; i++) {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        if (x * x + y * y <= 1) {
            inside_circle++;
        }
    }
    
    pi = (double)inside_circle / num_iterations * 4;
    printf("Sequential Pi: %f\n", pi);
    
    return 0;
}
