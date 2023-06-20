#include <stdio.h>
#include <mpi.h>
#include <stdbool.h>
 
int main(int argc, char *argv[])
{
    
    bool estado = false;
    int rank, vueltas, size, siguiente;

    MPI_Init(&argc, &argv);
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0)
    {
        printf("Introduzca el numero de veces que desea que reboten los mensajes entre sí: ");
        scanf("%d", &vueltas);
        siguiente = 1;
        printf("Proceso %d envia %d al proceso %d\n", rank, vueltas, siguiente);
        MPI_Send(&vueltas, 1, MPI_INT, siguiente, 0, MPI_COMM_WORLD);
    }

    do {
        if(rank == 1) {
            if(estado==true){
                MPI_Recv(&vueltas, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, &status);
            }
            else{
                MPI_Recv(&vueltas, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
            }
        }
        else{
            MPI_Recv(&vueltas, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
        }
        printf("Proceso %d ha recibido %d\n", rank, vueltas);

        if(rank == 0){
            --vueltas; //disminuir num vueltas
      	 }
        if(vueltas > 0){
            if(rank==1){
                if(estado==true){
                    siguiente = 0;
                }else{
                    siguiente = 2;
                }
                estado = !estado; // cambio de estado
            }
            else{
                siguiente = 1;
            }
            MPI_Send(&vueltas, 1, MPI_INT, siguiente, 0, MPI_COMM_WORLD);
            printf("Proceso %d envia %d al proceso %d\n", rank, vueltas, siguiente);
        }

    } while (vueltas > 0);
    
    MPI_Finalize();
    return 0;
}
