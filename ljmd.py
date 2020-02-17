from ctypes import *

so_files = "lib/libljmd.so"

my_functions = CDLL(so_files)

def read_input(datafile):
	with open(datafile) as f:
		data = f.read()
		print(data)


class mdsys_t(Structure):
	_fields_ = [('natoms', c_int), ('nfi', c_int), ('nsteps', c_int),
				('dt', c_double), ('mass', c_double), ('epsilon', c_double),
				('sigma', c_double), ('box', c_double), ('rcut', c_double),
				('ekin', c_double), ('epot', c_double), ('temp', c_double), 
				('rx', POINTER(c_double)), ('ry', POINTER(c_double)), ('rz', POINTER(c_double)), 
				('vx', POINTER(c_double)), ('vy', POINTER(c_double)), ('vz', POINTER(c_double)), 
				('fx', POINTER(c_double)), ('fy', POINTER(c_double)), ('fz', POINTER(c_double))]

read_input("examples/argon_108.inp")
#my_functions.mdsys_t
