/*
  P1.9_seed
  Function: Unit test - Kinetic Energy Computation
  Contributor: Luis Leon

  Dependencies:
  - Struct: mdsys_t
  - Helpers: azzero, pbc
  - math
*/

#include <stdio.h>
#include <stdlib.h>

#include "ljmd.h"

/* Import all the constants and references */
#include "unit-test-c-ekin.h"

/*
  In this unit test we have the following DoF:
  1. Atom mass given in AUM
  2. Velocities in X, Y, Z
  3. Number of atoms (with a singularity in one)

  -----
  kboltz and mvsq2 are kept constant
*/

int main() {
  int err = 0;

  /* Create test object */
  mdsys_t SUT;

  /* Fill the velocities */
  int n;
  for (n = 0; n < n_test_cases; ++n) {
    int i;

    SUT.natoms = test_cases[n].natoms;
    SUT.mass = test_cases[n].mass;

    SUT.vx = (double *)malloc(SUT.natoms * sizeof(double));
    SUT.vy = (double *)malloc(SUT.natoms * sizeof(double));
    SUT.vz = (double *)malloc(SUT.natoms * sizeof(double));

    for (i = 0; i < test_cases[n].natoms; ++i) {
      SUT.vx[i] = test_cases[n].velocities[i][0];
      SUT.vy[i] = test_cases[n].velocities[i][1];
      SUT.vz[i] = test_cases[n].velocities[i][2];
    }

    /* Compute result */
    ekin(&SUT);

    free(SUT.vx);
    free(SUT.vy);
    free(SUT.vz);

    /* Verify */
    if (abs(SUT.ekin - test_cases[n].exp_ekin) > EPS ||
        abs(SUT.temp - test_cases[n].exp_temp) > EPS) {
      err += 1;
      printf("Test Case(%s): %u - FAILED\n", test_cases[n].case_name, n);
      printf("Got: %15.10f %15.10f, Expected: %15.10f %15.10f\n", SUT.ekin,
             SUT.temp, test_cases[n].exp_ekin, test_cases[n].exp_temp);
    } else {
      printf("Test Case(%s): %u - PASSED\n", test_cases[n].case_name, n);
    }
  }

  return err;
}