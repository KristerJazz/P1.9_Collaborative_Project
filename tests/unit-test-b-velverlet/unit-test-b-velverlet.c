#include "unit-test-b-velverlet.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/ljmd.h"


int main(int argc, char **argv) {
  int i;
  FILE *fp;
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
  sys.rx[0] = PX;
  sys.rx[1] = PXX;
  sys.rx[2] = PXXX;
  sys.ry[0] = PY;
  sys.ry[1] = PYY;
  sys.ry[2] = PYYY;
  sys.rz[0] = PZ;
  sys.rz[1] = PZZ;
  sys.rz[2] = PZZZ;
  for (i = 0; i < NATOMS; ++i) {
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
  if (fabs(sys.rx[0] - P0ex) > ep) {
    printf("Test #1 not passed\n");
    exit(1);
  }
  if (fabs(sys.ry[0] - P0ey) > ep) {
    printf("Test #2 not passed\n");
    exit(1);
  }
  if (fabs(sys.rz[0] - P0ez) > ep) {
    printf("Test #3 not passed\n");
    exit(1);
  }

  if (fabs(sys.rx[1] - P1ex) > ep) {
    printf("Test #4 not passed\n");
    exit(1);
  }
  if (fabs(sys.ry[1] - P1ey) > ep) {
    printf("Test #5 not passed\n");
    exit(1);
  }
  if (fabs(sys.rz[1] - P1ez) > ep) {
    printf("Test #6 not passed\n");
    exit(1);
  }

  if (fabs(sys.rx[2] - P2ex) > ep) {
    printf("Test #7 not passed\n");
    exit(1);
  }
  if (fabs(sys.ry[2] - P2ey) > ep) {
    printf("Test #8 not passed\n");
    exit(1);
  }
  if (fabs(sys.rz[2] - P2ez) > ep) {
    printf("Test #9 not passed\n");
    exit(1);
  }

  if (fabs(sys.vx[0] - V0ex) > ep) {
    printf("Test #10 not passed\n");
    exit(1);
  }
  if (fabs(sys.vy[0] - V0ey) > ep) {
    printf("Test #11 not passed\n");
    exit(1);
  }
  if (fabs(sys.vz[0] - V0ez) > ep) {
    printf("Test #12 not passed\n");
    exit(1);
  }

  if (fabs(sys.vx[1] - V1ex) > ep) {
    printf("Test #13 not passed\n");
    exit(1);
  }
  if (fabs(sys.vy[1] - V1ey) > ep) {
    printf("Test #14 not passed\n");
    exit(1);
  }
  if (fabs(sys.vz[1] - V1ez) > ep) {
    printf("Test #15 not passed\n");
    exit(1);
  }

  if (fabs(sys.vx[2] - V2ex) > ep) {
    printf("Test #16 not passed\n");
    exit(1);
  }
  if (fabs(sys.vy[2] - V2ey) > ep) {
    printf("Test #17 not passed\n");
    exit(1);
  }
  if (fabs(sys.vz[2] - V2ez) > ep) {
    printf("Test #18 not passed\n");
    exit(1);
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
