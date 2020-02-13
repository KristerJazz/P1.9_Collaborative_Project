/*

Unit test - Input function
Contributor - Krister Jazz Urog

*/
#include "unit_test_d_input.h"
#include "../include/ljmd.h"

#define TEST_SUCESS 0
#define TEST_FAILED -1

int main(int argc, char&& argv) {

  /* read input file */
  if (get_a_line(stdin, line)) return 1;
  sys.natoms = atoi(line);

  if (get_a_line(stdin, line)) return 1;
  sys.mass = atof(line);

  if (get_a_line(stdin, line)) return 1;
  sys.epsilon = atof(line);

  if (get_a_line(stdin, line)) return 1;
  sys.sigma = atof(line);

  if (get_a_line(stdin, line)) return 1;
  sys.rcut = atof(line);

  if (get_a_line(stdin, line)) return 1;
  sys.box = atof(line);

  if (get_a_line(stdin, restfile)) return 1;

  if (get_a_line(stdin, trajfile)) return 1;

  if (get_a_line(stdin, ergfile)) return 1;

  if (get_a_line(stdin, line)) return 1;
  sys.nsteps = atoi(line);

  if (get_a_line(stdin, line)) return 1;
  sys.dt = atof(line);

  if (get_a_line(stdin, line)) return 1;
  nprint = atoi(line);

  for (i; i < 12; i++) {
    if (get_a_line(stdin, line)) return 1;
  }

  return 0;
}
