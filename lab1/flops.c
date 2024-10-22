#include <stdio.h>
#include <time.h>

int main()
{
    int i;
    double a = 1.1, b = 2.2, c;
    long operations = 1000000000; // 1 billion operations

    clock_t start = clock();

    for (i = 0; i < operations; i++)
    {
        c = a * b;
    }

    clock_t end = clock();

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    double flops = (double)operations / time_spent;
    double flops_in_billion = flops / 1e9;
    double flops_in_million = flops / 1e6;

    double cpu_clock_speed = 2.4;                      // in GHz
    double cpu_clock_speed_hz = cpu_clock_speed * 1e9; // in Hz

    double clock_cycles = cpu_clock_speed_hz * time_spent;

    printf("Time taken: %f seconds\n", time_spent);
    printf("FLOPS: %e\n", flops);
    printf("FLOPS in billion: %f GFLOPS\n", flops_in_billion);
    printf("FLOPS in million: %f MFLOPS\n", flops_in_million);
    printf("CPU Clock Speed: %f GHz\n", cpu_clock_speed);
    printf("Clock Cycles: %e\n", clock_cycles);

    return 0;
}
