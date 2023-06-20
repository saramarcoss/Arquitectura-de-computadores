#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<math.h>

int main(int argc, char *argv[]) {
	int i, numProcs, rank, digito, decimal;
	int array[numProcs];
	MPI_Init(&argc, &argv); 

	MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	srand(time(NULL)+rank);
	int aleatorio = rand() % 2;

	//se lo envía al resto de procesos(MPI_Allgather)
	MPI_Allgather(&aleatorio, 1, MPI_INT, array, 1, MPI_INT, MPI_COMM_WORLD);

	for(i=0;i<numProcs;i++){
	    if(rank==i){
		printf("Soy el proceso %d y he generado el valor %d\n", rank, aleatorio);
	    }
	}

	if (rank == numProcs-1) {
		printf("El número binario es: ");
	for (i = 0; i < numProcs; i++)
		printf("%d", array[i]);
		printf("\n");
	}

	int potencia = pow(2, rank);
	int multiplicacion = potencia * array[numProcs - rank - 1];
	MPI_Reduce(&multiplicacion, &decimal, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if (rank == 0) {
		printf("El número decimal es: %d", decimal);
	}
MPI_Finalize();
return 0;
}
