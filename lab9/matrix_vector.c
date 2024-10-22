#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 8

int main(int argc, char *argv[])
{
    int rank, size, i, j;
    double matrix[N][N], vector[N], local_matrix[N][N], local_result[N], global_result[N];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rows_per_process = N / size;

    if (rank == 0)
    {
        printf("\nMatrix is :\n");
        for (i = 0; i < N; i++)
        {
            vector[i] = i + 1;
            for (j = 0; j < N; j++)
            {
                matrix[i][j] = i + j + 1;
                printf("%f ", matrix[i][j]);
            }
            printf("\n");
        }

        printf("\nVector is : \n");
        for (int i = 0; i < N; i++)
            printf("%f ", vector[i]);
        printf("\n");
    }

    MPI_Scatter(matrix, rows_per_process * N, MPI_DOUBLE, local_matrix, rows_per_process * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    MPI_Bcast(vector, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    for (i = 0; i < rows_per_process; i++)
    {
        local_result[i] = 0.0;
        for (j = 0; j < N; j++)
        {
            local_result[i] += local_matrix[i][j] * vector[j];
        }
    }

    MPI_Gather(local_result, rows_per_process, MPI_DOUBLE, global_result, rows_per_process, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("\nMatrix-Vector Multiplication Result:\n");
        for (i = 0; i < N; i++)
        {
            printf("%f ", global_result[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}
