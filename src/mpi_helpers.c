/*
  P1.9_seed
  Function: MPI Helpers
  Contributor: Luis Leon

  Dependencies:
  - MPI > 3.0
*/

#ifdef _MPI
#include <mpi.h>
#include <stdlib.h>

void ljmd_mpi_init() { MPI_Init(NULL, NULL); }

void ljmd_mpi_finalise() { MPI_Finalize(); }
#else

void ljmd_mpi_init() {}
void ljmd_mpi_finalise() {}

#endif /* _MPI */
