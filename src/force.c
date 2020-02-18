/*
  P1.9_seed
  Function: Force Computation (force())
  Contributor: Luis Leon

  Dependencies:
  - Struct: mdsys_t
  - Helpers: azzero, pbc
  - math
*/

#include <math.h>

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
  /* zero energy and forces */
  epot = 0.0;
  azzero(sys->fx, sys->natoms);
  azzero(sys->fy, sys->natoms);
  azzero(sys->fz, sys->natoms);

  double c12 = 4.0 * sys->epsilon * POW12(sys->sigma);
  double c6 = 4.0 * sys->epsilon * POW6(sys->sigma);
  double rcsq = POW2(sys->rcut);
 

#pragma omp parallel reduction (+:epot)
  {
  double ffac,rx,ry,rz;
  int i,j;
#pragma omp for schedule(static)
  for (i = 0; i < (sys->natoms) - 1; ++i) {
    for (j = i + 1; j < (sys->natoms); ++j) {


      /* get distance between particle i and j */
      rx = pbc(sys->rx[i] - sys->rx[j], 0.5 * sys->box);
      ry = pbc(sys->ry[i] - sys->ry[j], 0.5 * sys->box);
      rz = pbc(sys->rz[i] - sys->rz[j], 0.5 * sys->box);
      double rsq = POW2(rx) + POW2(ry) + POW2(rz);

      /* compute force and energy if within cutoff */
      if (rsq < rcsq) {
        double rinv2 = 1.0 / rsq;
        double rinv6 = POW3(rinv2);
        ffac = (12.0 * c12 * rinv6 - 6.0 * c6) * rinv6 * rinv2;
        epot += rinv6 * (c12 * rinv6 - c6); 


	rx *=ffac;
	ry *=ffac;
	rz *=ffac;
	#pragma omp atomic
        sys->fx[i] += rx;
	#pragma omp atomic
	sys->fy[i] += ry;
	#pragma	omp atomic
        sys->fz[i] += rz;
	#pragma	omp atomic
	sys->fx[j] -= rx;
	#pragma	omp atomic
	sys->fy[j] -= ry;
	#pragma	omp atomic
	sys->fz[j] -= rz;
          }
        }
      }
  sys->epot= epot;  
  } // end parallel region
   
}
