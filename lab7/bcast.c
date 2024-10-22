#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int worldsize, worldrank;

    MPI_Comm_size(MPI_COMM_WORLD, &worldsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &worldrank);

    int data = 0;

    if (worldrank == 0)
    {
        data = 4666;
    }

    MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Process %d received \'data: %d\' from process 0\n", worldrank, data);

    MPI_Finalize();
    return 0;
}