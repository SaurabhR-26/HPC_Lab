#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int data;

    MPI_Send(&rank, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
    printf("Process %d, sent data to %d\n", rank, (rank + 1) % size);
    MPI_Recv(&data, 1, MPI_INT, (((rank - 1) + size) % size), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Process %d, received data from %d\n", rank, ((rank - 1) + size) % size);

    MPI_Finalize();
    return 0;
}