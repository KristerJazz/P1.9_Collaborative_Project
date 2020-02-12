/*
  P1.9_seed
  Function: Velverlet Time Integration (velverlet())
  Contributor: Luis Leon

  Dependencies:
  - Struct: mdsys_t
  - Consts: mvsq2e (m*v^2 in kcal/mol)
*/

#include "../include/ljmd.h"

void velverlet(mdsys_t *sys) {
  int i;

  /* first part: propagate velocities by half and positions by full step */
  for (i = 0; i < sys->natoms; ++i) {
    propagate_position(sys, i);
    propagate_velocity(sys, i);
  }

  /* compute forces and potential energy */
  force(sys);

  /* second part: propagate velocities by another half step */
  for (i = 0; i < sys->natoms; ++i) {
    propagate_velocity(sys, i);
  }
}
