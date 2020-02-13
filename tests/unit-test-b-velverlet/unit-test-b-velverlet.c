#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../include/ljmd.h"
#include "unit-test-b-velverlet.h"

int main(int argc, char **argv) {
  int i;
  mdsys_t sys;
  sys.natoms = NATOMS;
  sys.mass = MASS;
  sys.epsilon = EPSILON;
  sys.sigma = SIGMA;
  sys.rcut = RCUT;
  sys.box = BOX;
  sys.nsteps = NSTEPS;
  sys.dt = DT;

  /* allocate memory */
  sys.rx = (double *)malloc(sys.natoms * sizeof(double));
  sys.ry = (double *)malloc(sys.natoms * sizeof(double));
  sys.rz = (double *)malloc(sys.natoms * sizeof(double));
  sys.vx = (double *)malloc(sys.natoms * sizeof(double));
  sys.vy = (double *)malloc(sys.natoms * sizeof(double));
  sys.vz = (double *)malloc(sys.natoms * sizeof(double));
  sys.fx = (double *)malloc(sys.natoms * sizeof(double));
  sys.fy = (double *)malloc(sys.natoms * sizeof(double));
  sys.fz = (double *)malloc(sys.natoms * sizeof(double));
  /* define input*/
  for (i = 0; i < NATOMS; ++i) {
    sys.rx[i] = P0x[i];
    sys.ry[i] = P0y[i];
    sys.rz[i] = P0z[i];
    sys.vx[i] = VX;
    sys.vy[i] = VY;
    sys.vz[i] = VZ;
    sys.fx[i] = FX;
    sys.fy[i] = FY;
    sys.fz[i] = FZ;
  }

  /* test */
  for (i = 0; i < NATOMS; ++i) {
    propagate_velocity(&sys, i);
    propagate_position(&sys, i);
    propagate_velocity(&sys, i);
  }

  /* verification */
  for (i = 0; i < NATOMS; ++i) {
    if (fabs(sys.rx[i] - Px[i]) > ep) {
      printf("Px TEST KO, aborting...\n");
      exit(1);
    }
    if (fabs(sys.ry[i] - Py[i]) > ep) {
      printf("Py TEST KO, aborting...\n");
      exit(1);
    }
    if (fabs(sys.rz[i] - Pz[i]) > ep) {
      printf("Pz TEST KO, aborting...\n");
      exit(1);
    }
    if (fabs(sys.vx[i] - Vx[i]) > ep) {
      printf("Vx TEST KO, aborting...\n");
      exit(1);
    }
    if (fabs(sys.vy[i] - Vy[i]) > ep) {
      printf("Vy TEST KO, aborting...\n");
      exit(1);
    }
    if (fabs(sys.vz[i] - Vz[i]) > ep) {
      printf("Vz TEST KO, aborting...\n");
      exit(1);
    }
  }

  printf("TEST PASSED\n");
  free(sys.rx);
  free(sys.ry);
  free(sys.rz);
  free(sys.vx);
  free(sys.vy);
  free(sys.vz);
  free(sys.fx);
  free(sys.fy);
  free(sys.fz);

  return 0;
}
