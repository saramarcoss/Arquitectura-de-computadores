#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
    int size, my_rank;
    int buffer[size];
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
 
 
    printf("Proceso %d, valor: %d\n", my_rank, my_rank);

    MPI_Allgather(&my_rank, 1, MPI_INT, buffer, 1, MPI_INT, MPI_COMM_WORLD);
    printf("El proceso %d tiene los valores:\n", my_rank);
    for (int i = 0; i < size; i++) {
        printf("%d\n", buffer[i]);
    }
 
    MPI_Finalize();
 
    return 0;
}
