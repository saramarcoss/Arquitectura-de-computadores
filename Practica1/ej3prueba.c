#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
  MPI_Status status;
  int num, rank, size, tag, next, from;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
 

  next = (rank + 1) % size;
  from = (rank + size - 1) % size;


  if (rank == 0) {
    printf("Introduce el numero de vueltas al anillo: ");
    scanf("%d", &num);

    printf("Proceso %d envia %d al proceso %d\n", rank, num, next);
    MPI_Send(&num, 1, MPI_INT, next, tag, MPI_COMM_WORLD); 
  }

  do{

    MPI_Recv(&num, 1, MPI_INT, from, tag, MPI_COMM_WORLD, &status);
    printf("Proceso %d ha recibido %d\n", rank, num);

    if (rank == 0) {
      --num;
    }
        
    printf("Proceso %d envia %d al proceso %d\n", rank, num, next);
    MPI_Send(&num, 1, MPI_INT, next, tag, MPI_COMM_WORLD);
  } while (num > 1);

  if (rank == 0)
    MPI_Recv(&num, 1, MPI_INT, from, tag, MPI_COMM_WORLD, &status);

  MPI_Finalize();
  return 0;
}
