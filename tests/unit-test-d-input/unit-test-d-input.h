#ifndef __UNIT_TEST_D_INPUT_H__
#define __UNIT_TEST_D_INPUT_H__

const int NATOMS = 108;               //natoms
const double MASS = 39.948;           // mass in AMU
const double EPSILON = 0.2379;        // epsilon in kcal/mol
const double SIGMA = 3.405;           // sigma in angstrom
const double RCUT = 8.5;              // rcut in angstrom
const double BOX = 17.1580;           // box length (in angstrom)
//char = argon_108.rest;              // restart
//char = argon_108.xyz;     		  // trajectory
//char = argon_108.dat;     		  //energies
const double NSTEPS = 10000;          //nr MD steps
const double DT = 5.0;                 //MD time step (in fs)
const double NPRINT= 100;              //output print frequency
