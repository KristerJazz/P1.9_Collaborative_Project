# P1.9_Collaborative_Project

| Master | Develop |
|--------|---------|
| ![](https://travis-ci.com/KristerJazz/P1.9_Collaborative_Project.svg?branch=master) | ![](https://travis-ci.com/KristerJazz/P1.9_Collaborative_Project.svg?branch=develop) |

Current revision: **v0.2**

## Description

This package contains simplified MD code with multi-threading.
parallelization for simulating atoms with a Lennard-Jones potential.

The bundled makefiles are set up to compile the executable once
with OpenMP disabled and once with OpenMP enabled with each build
placing the various object files in separate directories.

The examples directory contains 3 sets of example input decks
and the reference directory the corresponding outputs.

## Collaborators

* **Stefano Campanella**: stefanocampanella
* **Luis Leon**: lleon95
* **Mattia Carello**: mattiacmhpc
* **Jazz Urog**: KristerJazz

## Policies

1. Use merge instead of rebase
2. If merge conflict, report and look for the responsibles!
3. Two approvals in the Pull Request before merge
4. Before leaving your PC, push to remote
5. Do not touch others branch
6. Branch naming convention: `feature/<username>-<feature_name>`

## Compilation instructions

**Compile**

* Without MPI nor OpenMP: `make`
* With MPI but not OpenMP: `make WITH_MPI=1`
* With OpenMP but not MPI: `make WITH_OMP=1`
* With OpenMP and MPI: `make WITH_OMP=1 WITH_MPI=1`
  
**Running checks**

* Without MPI nor OpenMP: `make check`
* With MPI but not OpenMP: `make WITH_MPI=$NUM_PROCS check`
* With OpenMP but not MPI: `make WITH_OMP=$NUM_THREADS check`
* With OpenMP and MPI: `make WITH_OMP=$NUM_THREADS WITH_MPI=$NUM_PROCS check`

* pip install -r requirements.txt
* python -m pytest .

**Cleaning**

`make clean`

**Running**

Without MPI:

```bash
OMP_NUM_THREADS=$NUM_THREADS
LD_LIBRARY_PATH=lib

# Python
python3 ljmd.py $INPUT_FILE
# C
./ljmd.x < $INPUT_FILE
```

With MPI:

```bash
export OMP_NUM_THREADS=$NUM_THREADS
export LD_LIBRARY_PATH=lib

# Python
mpirun -np $NUM_PROCS python3 ljmd.py $INPUT_FILE
# C
mpirun -np $NUM_PROCS ./ljmd.x < $INPUT_FILE
```


### Requirements

* OpenMPI > 3
* GCC > 8
* pytest Python Module
* make

## Python wrapper and unittest
Assigned: Krister Jazz Urog
Github name - KristerJazz

We implemented a python wrapper that uses the share object compiled by a previously compiled and optimized code for `Lennard Jones potential MD code`.
You can refer to the above instructions on how to compile and use a specific version of the optimized code.
Options are available:

1. Serial
2. OMP-enabled
3. MPI-enabled
4. Hybrid MPI-OMP

Unit tests are done to check the C code function with the python as a wrapper.
Test cases are built for the cases that,

1. 2 particle is within the cutoff region
2. 2 particle is outside the cutoff region
3. 1 particle where we set the force manually

where each case is assigned to different values that are simply computable and verifiable.

The test cases where applied to the following function, 

1. Force function
2. Initial propagate function
3. Second propagate function.

such that the functions outputs correct values of the `position`, `velocity`, `force` is checked, whichever value is needed to be checked.

With the `TravisCI` we run both the C tests and the pytests for different versions of the code, `serial`, `omp` enabled, and `mpi-enabled`.
I also implemented regression test that involves the `LJMD` python `class` that served as a wrapper for the C code having the same test cases. 

The tests are added to the `TRAVIS-CI` for `CI/CD` purposes.


## Optimizations

Assigned: Stefano Campanella
Github name: stefanocampanella

A number of simple optimizations have been implemented: the inlining of the `pbc` function, safe and unsafe compiler optimizations (through compiler flags `-O3` and `-ffast-math`, which can be combined into `-Ofast`) and architecture specific optimization/instructions through `-march=native` (`-mtune=native` is redundant). Afterwards, an algorithmic optimization taking advantage of the Newtorn's third law was implemented (performance gains are reported in the perf directory). It has been put particular attention in avoiding useless expensive operations and caching the results whenever possible.

## MPI parallelization

Assigned: Luis Leon
Github name: lleon95

The parallel MPI version of the program has been implemented. This parallel version leverage a replicated data approach and has been implemented in C using OpenMPI (basically, at each iteration the position of the particles is broadcasted and the value of the forces/potential energy is reduced). The code has been integrated with the rest of the project (Python wrapper, Morse potential, etc.). In particular, the Python integration has been provided by means of some utility functions (ex. the MPI initialize/finalize functions) and the environment variable provided by the MPI standard.

## OpenMP parallelization

Assigned: Mattia Carello
Github name: mattiacmhpc

The most computational demanding function of the code is `force(mdsys_t *sys)`, as can be checked with`perf` most of the work is executed inside this function. The force function has been parallelized using OpenMP (the code can be compiled with `-Wall -Wextra` without warnings, the OpenMP sections of code has been guarded with preprocessor directives). Race conditions have been avoided through private variables (`i,j,ffac,rx,ry,rz`). Some implementation choices were the usage of the dynamic scheduler and atomic updates (instead of critical sections/mutexes).

## Bonus task: Morse Potential

The Morse potential has been added to the simulation and tested (it can be enabled at compile time, with the `-DWITH_MORSE` flag). The format of the input files is the same, the `epsilon` and `sigma` parameters are converted to the ones used by the Morse potential during the reading of the input. This conversion is made by requiring that the position, depth and width of the minimum of the potential well is the same in both cases. 
