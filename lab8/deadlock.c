#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int message;
    MPI_Status status;

    if (rank == 0)
    {
        message = 100;
        MPI_Ssend(&message, 1, MPI_INT, 1, 101, MPI_COMM_WORLD);
        printf("Process 0: Sent message to Process 1.\n");

        MPI_Recv(&message, 1, MPI_INT, 1, 202, MPI_COMM_WORLD, &status);
        printf("Process 0: Received message from Process 1.\n");
    }
    else if (rank == 1)
    {
        message = 200;
        MPI_Ssend(&message, 1, MPI_INT, 0, 202, MPI_COMM_WORLD);
        printf("Process 1: Sent message to Process 0.\n");

        MPI_Recv(&message, 1, MPI_INT, 0, 101, MPI_COMM_WORLD, &status);
        printf("Process 1: Received message from Process 0.\n");
    }
    else
    {
        printf("Only two processes are required");
    }

    MPI_Finalize();
    return 0;
}
