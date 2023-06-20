#include <mpi.h>
#include <stdio.h>
 
int main(int argc, char *argv[])
{
    int rank,size,num;
    MPI_Status estado;
 
    MPI_Init(&argc, &argv); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    
    
    if(rank == 0){
    printf("Introduce el numero que desea transmitir: ");
    scanf("%d", &num);
    
 	printf("Proceso %d envia %d al proceso %d\n", rank, num, rank+1);
        MPI_Send(&num,1 ,MPI_INT,rank+1,0,MPI_COMM_WORLD); 
 
    }else{
        MPI_Recv(&num,1 ,MPI_INT,rank-1,0,MPI_COMM_WORLD,&estado); 
 
        printf("Soy el proceso %d y he recibido %d\n",rank, num);
        if(rank != size-1){
        printf("Proceso %d envia %d al proceso %d\n", rank, num, rank+1);
            MPI_Send(&num, 1 ,MPI_INT ,rank+1 , 0 ,MPI_COMM_WORLD);
            }
 
    }
    MPI_Finalize();
    return 0;
}


