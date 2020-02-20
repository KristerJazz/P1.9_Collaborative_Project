"""
Python wrapper for LJMD C code

Author: Krister Jazz Urog
Date: 17 February, 2020
"""
from ctypes import *
import sys
import os
from mpi4py import MPI

if MPI._sizeof(MPI.Comm) == sizeof(c_int):
    MPI_Comm = c_int
else:
    MPI_Comm = c_void_p

class MDSYS_T(Structure):
    """
    Molecular dynamics system structure object wrapper for a similar C struct.

    -----------------------------------------------
    Parameters:
            natoms = number of atoms
            nfi = current iteration step
            nsteps = total number of iteration steps
            dt = time step
            mass = mass of atom
            epsilon = constant
            sigma =  constant
            box = box size
            rcut = cutoff threshold distance
            ekin = Kinetic energy
            epot = Potential energy
            temp = Temperature
    """
    _fields_ = [('natoms', c_int), ('nfi', c_int), ('nsteps', c_int),
                ('dt', c_double), ('mass', c_double), ('epsilon', c_double),
                ('sigma', c_double), ('box', c_double), ('rcut', c_double),
                ('ekin', c_double), ('epot', c_double), ('temp', c_double),
                ('rx', POINTER(c_double)), ('ry', POINTER(c_double)), ('rz', POINTER(c_double)),
                ('vx', POINTER(c_double)), ('vy', POINTER(c_double)), ('vz', POINTER(c_double)),
                ('fx', POINTER(c_double)), ('fy', POINTER(c_double)), ('fz', POINTER(c_double)),
                ("mid", c_int), ("msize", c_int), ("mcom", MPI_Comm)]


class LJMD:
    def __init__(self, so_file):
        try:
            self._ljmd = CDLL(so_file)
        except:
            print("Please use the valid LJMD shared object file")
            raise

    def ljmd_mpi_init(self):
        self._ljmd.ljmd_mpi_init()

    def ljmd_mpi_finalise(self):
        self._ljmd.ljmd_mpi_finalise()

    def initialize_system(self, input_file):
        m_comm = MPI.COMM_WORLD
        m_comm_ptr = MPI._addressof(m_comm)
        m_comm_val = MPI_Comm.from_address(m_comm_ptr)
        rank = int(m_comm.Get_rank())
        if rank == 0:
            data = self.read_input(input_file)
        else:
            data = None
        data = m_comm.bcast(data, root=0)

        try:
            self.natoms = int(data[0])
            self.mass = float(data[1])
            self.epsilon = float(data[2])
            self.sigma = float(data[3])
            self.rcut = float(data[4])
            self.box = float(data[5])
            self.restfile = data[6]
            self.trajfile = data[7]
            self.ergfile = data[8]
            self.nsteps = int(data[9])
            self.dt = float(data[10])
            self.nprint = int(data[11])
        except:
            print("Please check values of your input file")
            raise

        self.sys = MDSYS_T(natoms=self.natoms,
                           mass=self.mass,
                           epsilon=self.epsilon,
                           sigma=self.sigma,
                           rcut=self.rcut,
                           box=self.box,
                           nsteps=self.nsteps,
                           dt=self.dt)

        self.sys.rx = (c_double * self.natoms)()
        self.sys.ry = (c_double * self.natoms)()
        self.sys.rz = (c_double * self.natoms)()
        self.sys.vx = (c_double * self.natoms)()
        self.sys.vy = (c_double * self.natoms)()
        self.sys.vz = (c_double * self.natoms)()
        self.sys.fx = (c_double * self.natoms)()
        self.sys.fy = (c_double * self.natoms)()
        self.sys.fz = (c_double * self.natoms)()
        self.sys.msize =int(m_comm.Get_size())
        self.sys.mid = int(m_comm.Get_rank())
        self.sys.mcom = m_comm_val

        example_path = ""

        if "EXAMPLES_PATH" in os.environ.keys():
           example_path = os.environ["EXAMPLES_PATH"] + "/" + self.restfile 

        if example_path == "":
           example_path = "examples/" + self.restfile
        
        if rank == 0:
            self.restart(example_path)

            self.force()
            self.ekin()
        self.sys.nfi = 0

    def run_simulation(self):
        master = True
        if int(self.sys.mid) != 0:
            master = False

        # Open Writes initial
        if master:
            print("Running simulation - Steps: ", self.sys.nsteps)
            self.erg = open(self.ergfile, 'w')
            self.traj = open(self.trajfile, 'w')
            self.write_output()

        self.sys.nfi = 1

        while self.sys.nfi <= self.sys.nsteps:
            if master:
                if (self.sys.nfi % self.nprint) == 0:
                    self.write_output()
                    if self.sys.nfi == self.sys.nsteps:
                        break
                self.propagate1()

            self.force()

            if master:
                self.propagate2()
                self._ljmd.ekin(byref(self.sys))
            self.sys.nfi += 1

        # Close the files
        if master:
            print("Done simulation")
            self.erg.close()
            self.traj.close()

    def propagate1(self):
        self._ljmd.initial_propagation(byref(self.sys))

    def force(self):
        self._ljmd.force(byref(self.sys))

    def propagate2(self):
        self._ljmd.final_propagation(byref(self.sys))

    def ekin(self):
        self._ljmd.ekin(byref(self.sys))

    def write_output(self):
        self.erg.write(
            "% 8d % 20.8f % 20.8f % 20.8f % 20.8f\n" %
            (self.sys.nfi,
             self.sys.temp,
             self.sys.ekin,
             self.sys.epot,
             self.sys.ekin +
             self.sys.epot))

        self.traj.write(
            "%d\n nfi=%d etot=%20.8f\n" %
            (self.sys.natoms,
             self.sys.nfi,
             self.sys.ekin +
             self.sys.epot))

        for i in range(self.natoms):
            self.traj.write(
                "Ar  %20.8f %20.8f %20.8f\n" %
                (self.sys.rx[i], self.sys.ry[i], self.sys.rz[i]))

    def read_input(self, datafile):
        try:
            with open(datafile) as f:
                data = [x.split()[0] for x in f.readlines()]
        except FileNotFoundError:
            print("Missing input file: Please provide correct file path")
            raise

        assert(
            len(data) == 12),\
			"Invalid input file: File should have 12 rows of input values"

        return data

    def restart(self, restfile):
        try:
        	with open(restfile) as f:
        	    r = f.readlines()
        	    assert(
        	        len(r) == 2 * self.natoms),\
					"Invalid restart file: File should have rows equal to twice the number of atoms\n"

        	    for i in range(self.natoms):
        	        self.sys.rx[i] = float(r[i].split()[0])
        	        self.sys.ry[i] = float(r[i].split()[1])
        	        self.sys.rz[i] = float(r[i].split()[2])

        	    for i in range(self.natoms):
        	        self.sys.vx[i] = float(r[i + self.natoms].split()[0])
        	        self.sys.vy[i] = float(r[i + self.natoms].split()[1])
        	        self.sys.vz[i] = float(r[i + self.natoms].split()[2])

        except FileNotFoundError:
            print("Please check if you have the correct path for the restart file")
            raise
        except:
            raise


try:
    input_path = sys.argv[1]
except:
    raise

so_path = "lib/libljmd.so"

if "ROOT_DIR" in os.environ.keys():
    if os.environ["ROOT_DIR"] != "":
        so_path = os.environ["ROOT_DIR"] + "/" + so_path

comm = MPI.COMM_WORLD
rank = comm.Get_rank()

main = LJMD(so_path)
#main.ljmd_mpi_init()
main.initialize_system(input_path)
main.run_simulation()
exit(0)
#main.ljmd_mpi_finalise()
