/*

Unit test - Input function
Contributor - Krister Jazz Urog

*/
#include "unit-test-d-input.h"

#include <stdlib.h>

#include "../include/ljmd.h"

#define TEST_SUCCESS 0
#define TEST_FAILED -1

int test_equality(double in, double test_value) {
  if (in == test_value)
    return 1;
  else
    return 0;
}

int main(int argc, char **argv) {
  char restfile[BLEN], trajfile[BLEN], ergfile[BLEN], line[BLEN];
  // int testing_progress=0;

  /* read input file */
  puts("============BEGIN TESTS=============");
  printf("Reading number of atoms: ");
  if (get_a_line(stdin, line)) return 1;
  int natoms = atoi(line);
  if (test_equality(natoms, NATOMS)) printf("Test success\n");

  printf("Reading mass of atoms: ");
  if (get_a_line(stdin, line)) return 1;
  double mass = atof(line);
  if (test_equality(mass, MASS)) printf("Test success\n");

  printf("Reading epsilon: ");
  if (get_a_line(stdin, line)) return 1;
  double epsilon = atof(line);
  if (test_equality(epsilon, EPSILON)) printf("Test success\n");

  printf("Reading sigma: ");
  if (get_a_line(stdin, line)) return 1;
  double sigma = atof(line);
  if (test_equality(sigma, SIGMA)) printf("Test success\n");

  printf("Reading RCUT: ");
  if (get_a_line(stdin, line)) return 1;
  double rcut = atof(line);
  if (test_equality(rcut, RCUT)) printf("Test success\n");

  printf("Reading BOX LENGTH: ");
  if (get_a_line(stdin, line)) return 1;
  double box = atof(line);
  if (test_equality(box, BOX)) printf("Test success\n");

  printf("Reading RESTFILE: ");
  if (get_a_line(stdin, restfile)) return 1;
  printf("Test success\n");

  printf("Reading TRAJFILE: ");
  if (get_a_line(stdin, trajfile)) return 1;
  printf("Test success\n");

  printf("Reading ERGFILE: ");
  if (get_a_line(stdin, ergfile)) return 1;
  printf("Test success\n");

  printf("Reading NSTEPS: ");
  if (get_a_line(stdin, line)) return 1;
  int nsteps = atoi(line);
  if (test_equality(nsteps, NSTEPS)) printf("Test success\n");

  printf("Reading DT: ");
  if (get_a_line(stdin, line)) return 1;
  double dt = atof(line);
  if (test_equality(dt, DT)) printf("Test success\n");

  printf("Reading NPRINT: ");
  if (get_a_line(stdin, line)) return 1;
  int nprint = atoi(line);
  if (test_equality(nprint, NPRINT)) printf("Test success\n");

  puts("============END TESTS=============");

  return 0;
}
