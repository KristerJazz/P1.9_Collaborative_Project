from ctypes import *

so_files = "lib/libljmd.so"

ljmd = CDLL(so_files)


class MDSYS_T(Structure):
	_fields_ = [('natoms', c_int), ('nfi', c_int), ('nsteps', c_int),
				('dt', c_double), ('mass', c_double), ('epsilon', c_double),
				('sigma', c_double), ('box', c_double), ('rcut', c_double),
				('ekin', c_double), ('epot', c_double), ('temp', c_double), 
				('rx', POINTER(c_double)), ('ry', POINTER(c_double)), ('rz', POINTER(c_double)), 
				('vx', POINTER(c_double)), ('vy', POINTER(c_double)), ('vz', POINTER(c_double)), 
				('fx', POINTER(c_double)), ('fy', POINTER(c_double)), ('fz', POINTER(c_double))]
	

class LJMD:
	def __init__(self, input_file):
		self.time_step = 0

		input_data = self.read_input(input_file)

		#self.initialize_values(input_data)

	

	def initialize_values(self, data):
		self.sys = MDSYS_T(natoms=data[0],
							mass=data[1],
							epsilon=data[2],
							sigma=data[3],
							rcut=data[4],
							box=data[5],
							restfile=data[6],
							trajfile=data[7],
							ergfile=data[8],
							nsteps=data[9],
							dt=data[10],
							nprint=data[11])

	def read_input(self, datafile):
		with open(datafile) as f:
			data = [x.split(' ')[0] for x in f.readlines()] 
			print(data)


main = LJMD("examples/argon_108.inp")
