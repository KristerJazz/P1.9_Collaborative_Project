#include "mpi.h"
#include "stdio.h"

void init()
{
  MPI_Init(NULL,NULL);
}

int hello()
{
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  printf("Rank %i, Size %i\n", world_rank, world_size);
  return 0;
}


void finalise()
{
  MPI_Finalize();
}
