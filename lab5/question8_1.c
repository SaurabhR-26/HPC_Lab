#include <stdio.h>
#include <time.h>
#define ARRAY_SIZE 1000000

long long sequential_sum(int arr[], int size)
{
    long long sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += arr[i];
    }
    return sum;
}

int main()
{
    int arr[ARRAY_SIZE];

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        arr[i] = i + 1;
    }

    clock_t start = clock();
    long long sum = sequential_sum(arr, ARRAY_SIZE);
    clock_t end = clock();
    printf("Sequential Sum: %lld\n", sum);
    printf("Time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);  

    return 0;
}
