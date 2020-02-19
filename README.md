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
