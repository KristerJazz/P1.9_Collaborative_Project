/*
  P1.9_seed
  Function: Force Computation (force())
  Contributor: Luis Leon

  Dependencies:
  - Struct: mdsys_t
  - Constants: mvsq2e, kboltz
*/

#include "ljmd.h"

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