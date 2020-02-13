#ifndef __UNIT_TEST_C_EKIN_H__
#define __UNIT_TEST_C_EKIN_H__

#include <string.h>

/* Unit test case */
typedef struct unit_case{
  int natoms;
  double mass;
  double velocities[10][3];
  double exp_ekin;
  double exp_temp;
  char case_name[16];
} unit_case_t;

/* Test cases */
const unit_case_t test_cases[] = {
  /* Weird case */
  {.natoms = 3, .mass = 12.34, 
    .velocities[0] = {1,2,3},
    .velocities[1] = {2,2,2},
    .velocities[2] = {0,2,3},
    .exp_ekin = 1861821.22383153,
    .exp_temp = 312301218.897113,
    .case_name = "Weird case"},
  /* Happy case */
  {.natoms = 3, .mass = 39.948, 
    .velocities[0] = {5.3072557614502406e-04, -1.9182563618355668e-03, 6.6929180130627429e-04},
    .velocities[1] = {-1.6469389079891580e-03, -3.3913862865732141e-04, -3.4603537121251295e-04},
    .velocities[2] = {-7.4215102626457323e-04, -9.8513589889560684e-05, 8.8892011842225927e-04},
    .exp_ekin = 0.415671348661546,
    .exp_temp = 69.7245617280353,
    .case_name = "Happy case"},
  /* Negative mass case */
  {.natoms = 3, .mass = -48.2, 
    .velocities[0] = {5.3072557614502406e-04, -1.9182563618355668e-03, 6.6929180130627429e-04},
    .velocities[1] = {-1.6469389079891580e-03, -3.3913862865732141e-04, -3.4603537121251295e-04},
    .velocities[2] = {-7.4215102626457323e-04, -9.8513589889560684e-05, 8.8892011842225927e-04},
    .exp_ekin = -0.501535971900634,
    .exp_temp = -84.1274625836414,
    .case_name = "Negative mass"},
  /* Zero-mass case */
  {.natoms = 3, .mass = 0, 
    .velocities[0] = {5.3072557614502406e-04, -1.9182563618355668e-03, 6.6929180130627429e-04},
    .velocities[1] = {-1.6469389079891580e-03, -3.3913862865732141e-04, -3.4603537121251295e-04},
    .velocities[2] = {-7.4215102626457323e-04, -9.8513589889560684e-05, 8.8892011842225927e-04},
    .exp_ekin = 0,
    .exp_temp = 0,
    .case_name = "Zero mass"},
  /* Single Atom case */
  {.natoms = 1, .mass = 23.23, 
    .velocities[0] = {5.3072557614502406e-04, -1.9182563618355668e-03, 6.6929180130627429e-04},
    .exp_ekin = 0.122405238886546,
    .exp_temp = 0,
    .case_name = "Single Atom"},
  /* Double Atom case */
  {.natoms = 2, .mass = 26.5, 
    .velocities[0] = {5.3072557614502406e-04, -1.9182563618355668e-03, 6.6929180130627429e-04},
    .velocities[1] = {-1.6469389079891580e-03, -3.3913862865732141e-04, -3.4603537121251295e-04},
    .exp_ekin = 0.232967297726934,
    .exp_temp = 78.1557005710359,
    .case_name = "Two atoms"},
};
const int n_test_cases = 6;

/* Unit test constants */
const unsigned int EPS = 1e-7;

#endif