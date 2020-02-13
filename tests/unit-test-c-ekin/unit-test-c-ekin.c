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
// FIXME: #include "ljmd.h"
/* Import all the constants and references */
#include "unit-test-c-ekin.h"

/* FIXME: delete all this when it is ready */
const double kboltz=0.0019872067;    
const double mvsq2e=2390.05736153349;
struct _mdsys {
    int natoms,nfi,nsteps;
    double dt, mass, epsilon, sigma, box, rcut;
    double ekin, epot, temp;
    double *rx, *ry, *rz;
    double *vx, *vy, *vz;
    double *fx, *fy, *fz;
};
typedef struct _mdsys mdsys_t;

void ekin(mdsys_t *sys) {
  int i;

  sys->ekin = 0.0;
  for (i = 0; i < sys->natoms; ++i) {
    sys->ekin += 0.5 * mvsq2e * sys->mass *
                 (sys->vx[i] * sys->vx[i] + sys->vy[i] * sys->vy[i] +
                  sys->vz[i] * sys->vz[i]);  //(1/2)mv^2
  }
  sys->temp = 2.0 * sys->ekin / (3.0 * sys->natoms - 3.0) / kboltz;
}

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