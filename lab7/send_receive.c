#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{

    MPI_Init(&argc, &argv);

    int world_size, world_rank;

    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int number;

    if (world_rank == 0)
    {
        number = 46;
        MPI_Send(&number, 1, MPI_INT, 1, 101, MPI_COMM_WORLD);
    }
    else
    {
        // means world_rank is 1
        MPI_Status status;
        MPI_Recv(&number, 1, MPI_INT, 0, 101, MPI_COMM_WORLD, &status);
        printf("Process 1 receive number %d from process 0 with statustag as %d\n", number, status.MPI_TAG);
    }

    MPI_Finalize();
    return 0;
}