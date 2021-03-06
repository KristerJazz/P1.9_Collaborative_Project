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
#ifdef _MPI
#include <mpi.h>
#endif

#include "ljmd.h"

#include <stdio.h>

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
  int i, j;
  double ffac, rx, ry, rz, epot;

  /* Get the rank */
  int natoms, natoms_res, start_index, end_index;
#ifdef _MPI
  /* Get the rank */
  int mid, msize;
  mid = sys->mid;
  msize = sys->msize;
#else
  const int mid = 0, msize = 1;
#endif /* _MPI */
  /* Number of atoms per process */
  natoms = sys->natoms / msize;
  natoms_res = sys->natoms % msize;

  if (mid < natoms_res) natoms++;

  /* Indexes */
  if (mid < natoms_res) {
    start_index = mid * natoms;
    end_index = start_index + natoms;
  } else {
    start_index = (natoms_res * (natoms + 1)) + natoms * (mid - natoms_res);
    end_index = start_index + natoms;
  }
  if (mid == (msize - 1)) end_index -= 1;

  /* zero energy and forces */
  epot = 0.0;
  azzero(sys->fx, sys->natoms);
  azzero(sys->fy, sys->natoms);
  azzero(sys->fz, sys->natoms);

#ifndef WITH_MORSE
  double c12 = 4.0 * sys->epsilon * POW12(sys->sigma);
  double c6 = 4.0 * sys->epsilon * POW6(sys->sigma);
#endif

  double rcsq = POW2(sys->rcut);

  /* Broadcasting important data */
#ifdef _MPI
  if (msize != 1) {
    MPI_Bcast(sys->rx, sys->natoms, MPI_DOUBLE, 0, sys->mcom);
    MPI_Bcast(sys->ry, sys->natoms, MPI_DOUBLE, 0, sys->mcom);
    MPI_Bcast(sys->rz, sys->natoms, MPI_DOUBLE, 0, sys->mcom);
  }
#endif /* _MPI */

#if defined(_OPENMP)
#pragma omp parallel reduction(+ : epot)
  {
#pragma omp for schedule(dynamic) private(i, j, ffac, rx, ry, rz)
#endif
    for (i = start_index; i < end_index; ++i) {
      double fx_i, fy_i, fz_i;
      fx_i = fy_i = fz_i = 0.0;
      for (j = i + 1; j < (sys->natoms); ++j) {
        /* get distance between particle i and j */
        rx = pbc(sys->rx[i] - sys->rx[j], 0.5 * sys->box);
        ry = pbc(sys->ry[i] - sys->ry[j], 0.5 * sys->box);
        rz = pbc(sys->rz[i] - sys->rz[j], 0.5 * sys->box);
        double rsq = POW2(rx) + POW2(ry) + POW2(rz);

        /* compute force and energy if within cutoff */
        if (rsq < rcsq) {
#ifndef WITH_MORSE
          double rinv2 = 1.0 / rsq;
          double rinv6 = POW3(rinv2);
          
          ffac = (12.0 * c12 * rinv6 - 6.0 * c6) * rinv6 * rinv2;
          epot += rinv6 * (c12 * rinv6 - c6);
#else
          double r = sqrt(rsq);
          double exp_f = exp(-1.0 * sys->a * (r - sys->re));

          ffac = -2.0 * sys->De * sys->a * exp_f * (1 - exp_f) / r;
          epot += sys->De * POW2(1 - exp_f) - sys->De;
#endif

          rx *= ffac; 
          ry *= ffac; 
          rz *= ffac; 

          fx_i += rx;
          fy_i += ry;
          fz_i += rz;
#if defined(_OPENMP)
#pragma omp atomic
#endif
          sys->fx[j] -= rx;
#if defined(_OPENMP)
#pragma omp atomic
#endif
          sys->fy[j] -= ry;
#if defined(_OPENMP)
#pragma omp atomic
#endif
          sys->fz[j] -= rz;
        }
      }
#if defined(_OPENMP)
#pragma omp atomic
#endif
      sys->fx[i] += fx_i;
#if defined(_OPENMP)
#pragma omp atomic
#endif
      sys->fy[i] += fy_i;
#if defined(_OPENMP)
#pragma omp atomic
#endif
      sys->fz[i] += fz_i;
    }
#if defined(_OPENMP)
  }  // end parallel region
#endif

  /*
    The things that should be centralised are basically:
    - epot
    - fi
  */
#ifdef _MPI
  if (msize != 1) {
    if (!mid) {
      MPI_Reduce(MPI_IN_PLACE, sys->fx, sys->natoms, MPI_DOUBLE, MPI_SUM, 0,
                 sys->mcom);
      MPI_Reduce(MPI_IN_PLACE, sys->fy, sys->natoms, MPI_DOUBLE, MPI_SUM, 0,
                 sys->mcom);
      MPI_Reduce(MPI_IN_PLACE, sys->fz, sys->natoms, MPI_DOUBLE, MPI_SUM, 0,
                 sys->mcom);
    } else {
      MPI_Reduce(sys->fx, sys->fx, sys->natoms, MPI_DOUBLE, MPI_SUM, 0,
                 sys->mcom);
      MPI_Reduce(sys->fy, sys->fy, sys->natoms, MPI_DOUBLE, MPI_SUM, 0,
                 sys->mcom);
      MPI_Reduce(sys->fz, sys->fz, sys->natoms, MPI_DOUBLE, MPI_SUM, 0,
                 sys->mcom);
    }
    MPI_Reduce(&epot, &(sys->epot), 1, MPI_DOUBLE, MPI_SUM, 0, sys->mcom);
  } else {
    sys->epot = epot;
  }
#else
  sys->epot = epot;
#endif /* _MPI */
}
