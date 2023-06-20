#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


int main(int argc, char *argv[]) {
    
    int rank,numProcs;
    int sendbuf[4], recvbuf[4];
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (numProcs != 4) {
    printf("El numero de procesos tiene que ser 4.\n");
    }else{
    
        for (int i = 0; i < numProcs; i++) {
                    sendbuf[i] = (i + 1) + rank * numProcs;
            }
           printf("Proceso %d: ", rank);
              for (int i = 0; i < numProcs; i++) {
                printf("%d, ", sendbuf[i]);
            }
            printf("\n");
            
            MPI_Alltoall(&sendbuf, 1, MPI_FLOAT, &recvbuf, 1, MPI_INT, MPI_COMM_WORLD);
            
            printf("(Transposición) Proceso %d: ", rank);
            for (int i = 0; i < numProcs; i++) {
                printf("%d, ", recvbuf[i]);
            }
            printf("\n");
            
        }
    MPI_Finalize();
    return 0;
    }
