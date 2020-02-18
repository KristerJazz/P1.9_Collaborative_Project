/*
  P1.9_seed
  Function: MPI Helpers
  Contributor: Luis Leon

  Dependencies:
  - MPI > 3.0
*/

#ifdef _MPI
#include <mpi.h>

void mpi_init()
{
  MPI_Init(NULL, NULL);
}

void mpi_finalise()
{
  MPI_Finalize();
}
#else

void mpi_init(){}
void mpi_finalise(){}

#endif /* _MPI */