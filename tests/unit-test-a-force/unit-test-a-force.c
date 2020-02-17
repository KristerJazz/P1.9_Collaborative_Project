#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include "ljmd.h"

#define NATOMS 2
#define MASS 39.948
#define EPSILON 0.2379
#define SIGMA 3.405
#define RCUT 8.5
#define BOX 17.1580

#define FREF (-24.0 * EPSILON / SIGMA)
#define TOL 1e-7
#define TEST_SUCCESS 0
#define TEST_FAILED -1

inline bool cmp(double x, double y) { return fabs(x - y) < TOL; }

int test_in_x(mdsys_t* sys, bool* status) {
  sys->rx[1] = sys->sigma;
  sys->ry[1] = 0.0;
  sys->rz[1] = 0.0;

  azzero(sys->fx, sys->natoms);
  azzero(sys->fy, sys->natoms);
  azzero(sys->fz, sys->natoms);

  force(sys);

  if (cmp(sys->fx[0], FREF) && cmp(sys->fy[0], 0.0) && cmp(sys->fz[0], 0.0))
    return TEST_SUCCESS;
  else {
    *status = false;
    return TEST_FAILED;
  }
}

int test_in_y(mdsys_t* sys, bool* status) {
  sys->rx[1] = 0.0;
  sys->ry[1] = sys->sigma;
  sys->rz[1] = 0.0;

  azzero(sys->fx, sys->natoms);
  azzero(sys->fy, sys->natoms);
  azzero(sys->fz, sys->natoms);

  force(sys);

  if (cmp(sys->fx[0], 0.0) && cmp(sys->fy[0], FREF) && cmp(sys->fz[0], 0.0))
    return TEST_SUCCESS;
  else {
    *status = false;
    return TEST_FAILED;
  }
}

int test_in_z(mdsys_t* sys, bool* status) {
  sys->rx[1] = 0.0;
  sys->ry[1] = 0.0;
  sys->rz[1] = sys->sigma;

  azzero(sys->fx, sys->natoms);
  azzero(sys->fy, sys->natoms);
  azzero(sys->fz, sys->natoms);

  force(sys);

  if (cmp(sys->fx[0], 0.0) && cmp(sys->fy[0], 0.0) && cmp(sys->fz[0], FREF))
    return TEST_SUCCESS;
  else {
    *status = false;
    return TEST_FAILED;
  }
}

int test_out_x(mdsys_t* sys, bool* status) {
  sys->rx[1] = sys->box / 2;
  sys->ry[1] = 0.0;
  sys->rz[1] = 0.0;

  azzero(sys->fx, sys->natoms);
  azzero(sys->fy, sys->natoms);
  azzero(sys->fz, sys->natoms);

  force(sys);

  if (cmp(sys->fx[0], 0.0) && cmp(sys->fy[0], 0.0) && cmp(sys->fz[0], 0.0))
    return TEST_SUCCESS;
  else {
    *status = false;
    return TEST_FAILED;
  }
}

int test_out_y(mdsys_t* sys, bool* status) {
  sys->rx[1] = 0.0;
  sys->ry[1] = sys->box / 2;
  sys->rz[1] = 0.0;

  azzero(sys->fx, sys->natoms);
  azzero(sys->fy, sys->natoms);
  azzero(sys->fz, sys->natoms);

  force(sys);

  if (cmp(sys->fx[0], 0.0) && cmp(sys->fy[0], 0.0) && cmp(sys->fz[0], 0.0))
    return TEST_SUCCESS;
  else {
    *status = false;
    return TEST_FAILED;
  }
}

int test_out_z(mdsys_t* sys, bool* status) {
  sys->rx[1] = 0.0;
  sys->ry[1] = 0.0;
  sys->rz[1] = sys->box / 2;

  azzero(sys->fx, sys->natoms);
  azzero(sys->fy, sys->natoms);
  azzero(sys->fz, sys->natoms);

  force(sys);

  if (cmp(sys->fx[0], 0.0) && cmp(sys->fy[0], 0.0) && cmp(sys->fz[0], 0.0))
    return TEST_SUCCESS;
  else {
    *status = false;
    return TEST_FAILED;
  }
}

int main() {
  mdsys_t sys;
  bool status = true;

  sys.natoms = NATOMS;
  sys.mass = MASS;
  sys.epsilon = EPSILON;
  sys.sigma = SIGMA;
  sys.rcut = RCUT;
  sys.box = BOX;

  sys.rx = (double*)malloc(sys.natoms * sizeof(double));
  sys.ry = (double*)malloc(sys.natoms * sizeof(double));
  sys.rz = (double*)malloc(sys.natoms * sizeof(double));
  sys.fx = (double*)malloc(sys.natoms * sizeof(double));
  sys.fy = (double*)malloc(sys.natoms * sizeof(double));
  sys.fz = (double*)malloc(sys.natoms * sizeof(double));

  sys.rx[0] = 0.0;
  sys.ry[0] = 0.0;
  sys.rz[0] = 0.0;

  puts("==== BEGIN TESTS ====");
  printf("particles inside cutoff region, along x: %s\n",
         !test_in_x(&sys, &status) ? "PASSED" : "FAILED");
  printf("particles inside cutoff region, along y: %s\n",
         !test_in_y(&sys, &status) ? "PASSED" : "FAILED");
  printf("particles inside cutoff region, along z: %s\n",
         !test_in_z(&sys, &status) ? "PASSED" : "FAILED");
  printf("particles outside cutoff region, along x: %s\n",
         !test_out_x(&sys, &status) ? "PASSED" : "FAILED");
  printf("particles outside cutoff region, along y: %s\n",
         !test_out_y(&sys, &status) ? "PASSED" : "FAILED");
  printf("particles outside cutoff region, along z: %s\n",
         !test_out_z(&sys, &status) ? "PASSED" : "FAILED");
  puts("==== END TESTS ====");

  free(sys.rx);
  free(sys.ry);
  free(sys.rz);
  free(sys.fx);
  free(sys.fy);
  free(sys.fz);

  if (status)
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}
