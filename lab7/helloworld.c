#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int comm_size, comm_rank;

    MPI_Comm_rank(MPI_COMM_WORLD, &comm_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

    printf("Hello from process %d, out of %d processes\n", comm_rank, comm_size);

    MPI_Finalize();
    return 0;
}