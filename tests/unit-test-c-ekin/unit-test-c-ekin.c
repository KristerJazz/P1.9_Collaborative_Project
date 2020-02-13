/*
  P1.9_seed
  Function: Unit test - Kinetic Energy Computation
  Contributor: Luis Leon

  Dependencies:
  - Struct: mdsys_t
  - Helpers: azzero, pbc
  - math
*/

#include <stdlib.h>
#include <stdio.h>

#include "ljmd.h"

/* Import all the constants and references */
#include "unit-test-c-ekin.h"

int main() {
  int err = 0;

  /* Create test object */
  mdsys_t SUT;

  /* Fill the System Under Test with details */
  SUT.natoms = NATOMS;
  SUT.mass = MASS;
  SUT.vx = (double *) malloc(NATOMS * sizeof(double));
  SUT.vy = (double *) malloc(NATOMS * sizeof(double));
  SUT.vz = (double *) malloc(NATOMS * sizeof(double));

  /* Fill the velocities */
  int i;
  for(i = 0; i < NATOMS; ++i) {
    SUT.vx[i] = LUT_vel[i][0];
    SUT.vx[i] = LUT_vel[i][1];
    SUT.vx[i] = LUT_vel[i][2];
  }

  /* Compute result */
  ekin(&SUT);

  /* Verify */
  err += abs(SUT.ekin - EXPECTED_EKIN) > EPS;
  err += abs(SUT.temp - EXPECTED_TEMP) > EPS;

  return err;
}