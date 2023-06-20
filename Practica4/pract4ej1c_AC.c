#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
    int size,my_rank;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
 
 
    int my_values[size];
    for(int i = 0; i < size; i++)
    {
        my_values[i] = my_rank + i * 100;
    }
    printf("Valores del proceso %d:\n", my_rank);
    for(int i = 0; i < size; i++)
    {
        printf("%d\n", my_values[i]);
    }

 
    int buffer_recv[size];
    MPI_Alltoall(&my_values, 1, MPI_INT, buffer_recv, 1, MPI_INT, MPI_COMM_WORLD);
    printf("Valores recogidos en el proceso %d:\n", my_rank);
    for(int i = 0; i < size; i++)
    {
        printf("%d,", buffer_recv[i]);
    }
    printf("\n");
 
    MPI_Finalize();
 
    return 0;
}
