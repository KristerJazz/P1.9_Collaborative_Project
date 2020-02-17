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
	def __init__(self, input_file, cdll):
		self._ljmd = cdll
		self.time_step = 0

		data = self.read_input(input_file)

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

		self.initialize_system()

	def initialize_system(self):
		
		self.sys = MDSYS_T(natoms=self.natoms,
							mass=self.mass,
							epsilon=self.epsilon,
							sigma=self.sigma,
							rcut=self.rcut,
							box=self.box,
							nsteps = self.nsteps,
							dt=self.dt)

		self.sys.rx = (c_double*self.natoms)()
		self.sys.ry = (c_double*self.natoms)()
		self.sys.rz = (c_double*self.natoms)()
		self.sys.vx = (c_double*self.natoms)()
		self.sys.vy = (c_double*self.natoms)()
		self.sys.vz = (c_double*self.natoms)()
		self.sys.fx = (c_double*self.natoms)()
		self.sys.fy = (c_double*self.natoms)()
		self.sys.fz = (c_double*self.natoms)()

		self.restart("examples/"+self.restfile)

		self.force()
		self.ekin()
		self.sys.nfi = 0
	
	def force(self):
		print("The force awakens")
		self._ljmd.force(byref(self.sys))
	
	def ekin(self):
		self._ljmd.ekin(byref(self.sys))

	def run(self):
		print("Running simulation")

		while self.sys.nfi < self.nsteps:
			self._ljmd.velverlet(byref(self.sys))
			self._ljmd.ekin(byref(self.sys))
			
		print("Done simulation")
		
	def read_input(self, datafile):
		with open(datafile) as f:
			data = [x.split(' ')[0] for x in f.readlines()] 

		return data
	
	def restart(self, restfile):
		with open(restfile) as f:
			r = f.readlines()
			for i in range(self.natoms):
				self.sys.rx[0] = float(r[i].split()[0])
				self.sys.ry[0] = float(r[i].split()[1])
				self.sys.rx[0] = float(r[i].split()[2])

			#for i in range(self.natoms):
			#	v = f.readlines()
			#	self.sys.vx[0] = v.split()[0]
			#	self.sys.vy[0] = v.split()[1]
			#	self.sys.vx[0] = v.split()[2]



	

	def go(self):
		print(self.sys.fx[0])
		#for i in range(self.nsteps):
		#		print(self.sys.nfi)


main = LJMD("examples/argon_108.inp", ljmd)
main.go()
