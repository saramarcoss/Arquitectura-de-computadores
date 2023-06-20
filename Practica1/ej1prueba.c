#include <mpi.h>
#include<stdio.h>

int main(int argc, char** argv){
	int nproc;
	int myrank;
	double start, finish, tiempo;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
	
    MPI_Barrier(MPI_COMM_WORLD);
    start = MPI_Wtime();

    printf("Hola mundo, soy el proceso %d de un total de %d\n",myrank,nproc);
	
    MPI_Barrier(MPI_COMM_WORLD);
    finish = MPI_Wtime();
    tiempo = finish-start;
    printf("Tiempo de ejecucion proceso %d en segundos:%f\n", myrank, tiempo);
	MPI_Finalize();
}
