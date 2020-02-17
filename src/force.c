/*
  P1.9_seed
  Function: Force Computation (force())
  Contributor: Luis Leon

  Dependencies:
  - Struct: mdsys_t
  - Helpers: azzero, pbc
  - math
*/

#include <omp.h>
#include <math.h>
#include <stdlib.h>

#include "ljmd.h"

#define POW2(x) ((x) * (x))
#define POW3(x) (POW2(x) * (x))
#define POW6(x) (POW2(x) * POW2(x) * POW2(x))
#define POW12(x) (POW6(x) * POW6(x))

/* helper function: apply minimum image convention */
inline double pbc(double x, const double boxby2) {
  while (x > boxby2) x -= 2.0 * boxby2;
  while (x < -boxby2) x += 2.0 * boxby2;
  return x;
}

void force(mdsys_t *sys) {
  double epot;
  
  omp_lock_t * writelock;
  epot = 0;

  /* zero energy and forces */
  sys->epot = 0.0;
  azzero(sys->fx, sys->natoms);
  azzero(sys->fy, sys->natoms);
  azzero(sys->fz, sys->natoms);

  double c12 = 4.0 * sys->epsilon * POW12(sys->sigma);
  double c6 = 4.0 * sys->epsilon * POW6(sys->sigma);
  double rcsq = POW2(sys->rcut);

  writelock = (omp_lock_t *) malloc(sys->natoms * sizeof(omp_lock_t));

  int k = 0;

  /* Initialise the locks */
#pragma omp parallel
{
  
  #pragma omp for
  for(k = 0; k < (sys->natoms); ++k) {
    omp_init_lock(&writelock[k]);
  }
}

#pragma omp parallel reduction(+:epot)
{
  int i, j;
  int tid = omp_get_thread_num();
  int tsize = omp_get_num_threads();

  for (i = tid; i < (sys->natoms) - 1; i += tsize) {

    double rx, ry, rz;
    double fx, fy, fz;
    double ffac;

    fx = 0; fy = 0; fz = 0;

    for (j = i + 1; j < (sys->natoms); ++j) {

      if (i == j) continue;

      /* get distance between particle i and j */
      rx = pbc(sys->rx[i] - sys->rx[j], 0.5 * sys->box);
      ry = pbc(sys->ry[i] - sys->ry[j], 0.5 * sys->box);
      rz = pbc(sys->rz[i] - sys->rz[j], 0.5 * sys->box);
      double rsq = POW2(rx) + POW2(ry) + POW2(rz);

      /* compute force and energy if within cutoff */
      if (rsq < rcsq) {

        /* No race condition risk*/
        double rinv2 = 1.0 / rsq;
        double rinv6 = POW3(rinv2);
        ffac = (12.0 * c12 * rinv6 - 6.0 * c6) * rinv6 * rinv2;

        epot += rinv6 * (c12 * rinv6 - c6); 

        fx += rx * ffac; 
        fy += ry * ffac; 
        fz += rz * ffac; 

        omp_set_lock(&writelock[j]);
        sys->fx[j] -= rx * ffac;
        sys->fy[j] -= ry * ffac;
        sys->fz[j] -= rz * ffac;
        omp_unset_lock(&writelock[j]);

      }
    }

    omp_set_lock(&writelock[i]);
    sys->fx[i] += fx;
    sys->fy[i] += fy;
    sys->fz[i] += fz;
    omp_unset_lock(&writelock[i]);
    
  }
}
  sys->epot = epot;

  /* Free the locks */
#pragma omp parallel for
  for(k = 0; k < (sys->natoms); ++k) {
    omp_destroy_lock(&writelock[k]);
  }
  free(writelock);
}
