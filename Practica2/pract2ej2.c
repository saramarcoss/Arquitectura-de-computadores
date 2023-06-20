#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
    int rank,size,num;
    
    
    MPI_Status estado;
    MPI_Init(&argc, &argv); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    
    int datos[size];
    srand(time(NULL)+rank);
    num = rand() % 100;
   
    printf("Soy el proceso %d y he inicializado la variable con el dato %d\n", rank, num);
    if(rank == 0)
    {
        datos[0]=num;
        int i;
        for(int i = 1; i < size; i++)
        {
            MPI_Recv(&num, i, MPI_INT, i, 0, MPI_COMM_WORLD, &estado);
            datos[i] = num;
            printf("Soy el proceso %d y he recibido el valor %d del proceso %d\n", rank, num, i);
        }
        wait(datos);
        printf("Soy el proceso %d y ya he recibido los datos de los %d procesos: ", rank, size);
        for(i = 0; i < size; i++)
        {
            printf("dato proceso %d-> %d    ", i, datos[i]);
        }
        printf("\n");
    }
    else
    {
        MPI_Send(&num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();

    return 0;
}
