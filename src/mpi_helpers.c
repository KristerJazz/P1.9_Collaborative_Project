/*
  P1.9_seed
  Function: MPI Helpers
  Contributor: Luis Leon

  Dependencies:
  - MPI > 3.0
*/

void mpi_init()
{
  MPI_Init(NULL, NULL);
}

void mpi_finalise()
{
  MPI_Finalize();
}