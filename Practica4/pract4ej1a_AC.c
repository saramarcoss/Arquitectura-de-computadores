#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[])
{

    int my_rank,size;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
 
    // Cada proceso manda su rank al proceso 0
    int reduction_result = 0;
    MPI_Reduce(&my_rank, &reduction_result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
 
    if(my_rank ==0){
        printf("La suma de todos los ranks es %d.\n", reduction_result);
    }
 
    MPI_Finalize();
 
    return EXIT_SUCCESS;
}
