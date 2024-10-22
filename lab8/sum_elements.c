#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int rank, size;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // logic
    int arr[] = {2, 7, 9, 4, 7, 0, 1, 3, 5, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    int mid = n / 2.0;

    if (rank == 0)
    {

        printf("Number of elements: %d\n", n);
        printf("Elements of array are: ");

        for (int i = 0; i < n; i++)
            printf("%d ", arr[i]);
        printf("\n");

        int sum = 0;

        for (int j = 0; j <= mid; j++)
            sum += arr[j];
        printf("Process 0 sum: %d\n", sum);

        int recv_sum;

        MPI_Recv(&recv_sum, 1, MPI_INT, 1, 101, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 0 received sum %d from process 1\n", recv_sum);

        sum += recv_sum;
        printf("Total sum is: %d", sum);
    }
    else if (rank == 1)
    {
        int sum = 0;

        for (int j = mid + 1; j < n; j++)
            sum += arr[j];
        printf("Process 1 sum: %d\n", sum);

        MPI_Send(&sum, 1, MPI_INT, 0, 101, MPI_COMM_WORLD);
        printf("Process 1 sent %d sum to process 0\n", sum);
    }
    else
    {
        printf("Note: Only two processes are required\n");
    }

    MPI_Finalize();
    return 0;
}