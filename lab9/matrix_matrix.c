#include <stdio.h>
#include <mpi.h>

#define N 8

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank, size, rows_per_process;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    rows_per_process = N / size;

    int a[N][N], b[N][N], c[N][N];

    if (rank == 0)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                a[i][j] = i + j + 1;
                b[i][j] = i - j + 1;
                c[i][j] = 0;
            }
        }

        printf("\nMatrix A:\n");

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }

        printf("\nMatrix B:\n");

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                printf("%d ", b[i][j]);
            }
            printf("\n");
        }
    }

    int local_mat_a[rows_per_process][N];

    MPI_Scatter(a, rows_per_process * N, MPI_INT, local_mat_a, rows_per_process * N, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Bcast(b, N * N, MPI_INT, 0, MPI_COMM_WORLD);

    int local_mat_c[rows_per_process][N];

    for (int i = 0; i < rows_per_process; i++)
    {
        for (int j = 0; j < N; j++)
        {
            local_mat_c[i][j] = 0;
            for (int k = 0; k < N; k++)
            {
                local_mat_c[i][j] += (local_mat_a[i][k] * b[k][j]);
            }
        }
    }

    MPI_Gather(local_mat_c, rows_per_process * N, MPI_INT, c, rows_per_process * N, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("\nMat-Mat multiplication result:\n");

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                printf("%d ", c[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();
    return 0;
}