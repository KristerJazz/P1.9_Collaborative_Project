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

		data = self.read_input(input_file)

		self.natoms=int(data[0])
		self.mass=float(data[1])
		self.epsilon=float(data[2])
		self.sigma=float(data[3])
		self.rcut=float(data[4])
		self.box=float(data[5])
		self.restfile=data[6]
		self.trajfile=data[7]
		self.ergfile=data[8]
		self.nsteps=int(data[9])
		self.dt=float(data[10])
		self.nprint=int(data[11])

		self.initialize_system()

	def initialize_system(self):
		
		self.sys = MDSYS_T(natoms=self.natoms,
							nfi=0,
							mass=self.mass,
							epsilon=self.epsilon,
							sigma=self.sigma,
							rcut=self.rcut,
							box=self.box,
							nsteps = self.nsteps,
							dt=self.dt)
	
	def force(self):
		ljmd.force(byref(self.sys))

	def ekin(self):
		ljmd.ekin(byref(self.sys))
		
		



	def read_input(self, datafile):
		with open(datafile) as f:
			data = [x.split(' ')[0] for x in f.readlines()] 
			print(data)

		return data


main = LJMD("examples/argon_108.inp")
