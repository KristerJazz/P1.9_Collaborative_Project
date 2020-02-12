#ifndef __LJMD__
#define __LJMD__

/** 
 * @brief structure to hold the complete information 
 * about the MD system 
 */
struct _mdsys {
    int natoms,nfi,nsteps;
    double dt, mass, epsilon, sigma, box, rcut;
    double ekin, epot, temp;
    double *rx, *ry, *rz;
    double *vx, *vy, *vz;
    double *fx, *fy, *fz;
};
typedef struct _mdsys mdsys_t;

/**
 * @brief boltzman constant in kcal/mol/K 
 */
const double kboltz=0.0019872067;     

/**
 * @brief conversion constant: m*v^2 in kcal/mol
 */
const double mvsq2e=2390.05736153349;

/**
 * @brief helper function: read a line and then return
 *  the first string with whitespace stripped off 
 */
static int get_a_line(FILE *fp, char *buf);

/**
 * @brief helper function: zero out an array 
 */
static void azzero(double *d, const int n);


/**
 * @brief helper function: apply minimum image convention
 */
static double pbc(double x, const double boxby2);

/**
 * @brief compute kinetic energy 
 */
static void ekin(mdsys_t *sys);


/**
 * @brief compute forces 
 */
static void force(mdsys_t *sys);


/**
 * @brief velocity verlet 
 */
static void velverlet(mdsys_t *sys);

/**
 * @brief propagate positions
 */
void propagate_position(mdsys_t *sys, int i);

/**
 * @brief propagate velocities
 */
void propagate_velocity(mdsys_t *sys, int i);


/**
 * @brief append data to output. 
 */
static void output(mdsys_t *sys, FILE *erg, FILE *traj);

#endif
