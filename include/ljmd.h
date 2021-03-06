/* 
 * simple lennard-jones potential MD code with velocity verlet.
 * units: Length=Angstrom, Mass=amu; Energy=kcal
 *
 * baseline c version.
 *
 * author: Stefano Campanella
 */

#ifndef __LJMD__
#define __LJMD__

#ifdef _MPI
#include <mpi.h>
#endif

#include <stdio.h>

/**
 * @brief generic file- or pathname buffer length 
 */
#define BLEN 200

/**
 * @brief structure to hold the complete information
 * about the MD system
 */
struct _mdsys {
  int natoms, nfi, nsteps;
#ifndef WITH_MORSE
  double dt, mass, epsilon, sigma, box, rcut;
#else
  double dt, mass, box, rcut, De, a, re;
#endif
  double ekin, epot, temp;
  double *rx, *ry, *rz;
  double *vx, *vy, *vz;
  double *fx, *fy, *fz;
#if _MPI
  int mid, msize;
  MPI_Comm mcom;
#endif
};
typedef struct _mdsys mdsys_t;

/**
 * @brief boltzman constant in kcal/mol/K
 */
extern const double kboltz;

/**
 * @brief conversion constant: m*v^2 in kcal/mol
 */
extern const double mvsq2e;

/**
 * @brief helper function: read a line and then return
 *  the first string with whitespace stripped off
 */
int get_a_line(FILE *fp, char *buf);

/**
 * @brief helper function: zero out an array
 */
void azzero(double *d, const int n);

/**
 * @brief compute kinetic energy
 */
void ekin(mdsys_t *sys);

/**
 * @brief compute forces
 */
void force(mdsys_t *sys);

/**
 * @brief first propagation
 */
void initial_propagation(mdsys_t *sys);

/**
 * @brief last propagation
 */
void final_propagation(mdsys_t *sys);

/**
 * @brief append data to output.
 */
void output(mdsys_t *sys, FILE *erg, FILE *traj);

#endif
