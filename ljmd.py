"""
Python wrapper for LJMD C code

Author: Krister Jazz Urog
Date: 17 February, 2020
"""
from ctypes import *
import sys

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
				('fx', POINTER(c_double)), ('fy', POINTER(c_double)), ('fz', POINTER(c_double))] 

class LJMD:
	def __init__(self, so_file, input_file):
		self._ljmd = CDLL(so_file)
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

	def run_simulation(self):
		print("Running simulation")

		self.erg = open(self.ergfile, 'w')
		self.traj = open(self.trajfile, 'w')
		self.write_output()
		self.sys.nfi = 1
		while self.sys.nfi <= self.sys.nsteps:
			if (self.sys.nfi%self.nprint)==0:
				self.write_output()

			#self._ljmd.velverlet(byref(self.sys))
			self.propagate1()
			self.force()
			self.propagate2()
			self._ljmd.ekin(byref(self.sys))
			self.sys.nfi+=1
			
		print("Done simulation")
		
		self.erg.close()
		self.traj.close()
	
	def propagate1(self):
		for i in range(self.natoms):
			self._ljmd.propagate_velocity(byref(self.sys), i)
			self._ljmd.propagate_position(byref(self.sys), i)

	def force(self):
		self._ljmd.force(byref(self.sys))

	def propagate2(self):
		for i in range(self.natoms):
			self._ljmd.propagate_velocity(byref(self.sys), i)

	def ekin(self):
		print("Kinetic energy initialized")
		self._ljmd.ekin(byref(self.sys))
	
	def write_output(self):
		self.erg.write("% 8d % 20.8f % 20.8f % 20.8f % 20.8f\n" % (self.sys.nfi, self.sys.temp,
         				self.sys.ekin, self.sys.epot, self.sys.ekin + self.sys.epot))

		self.traj.write("%d\n nfi=%d etot=%20.8f\n" % (self.sys.natoms, self.sys.nfi, 
						self.sys.ekin + self.sys.epot))

		for i in range(self.natoms):
			self.traj.write("Ar  %20.8f %20.8f %20.8f\n" % (self.sys.rx[i], self.sys.ry[i],
         		   			self.sys.rz[i]))

	def read_input(self, datafile):
		with open(datafile) as f:
			data = [x.split()[0] for x in f.readlines()] 

		return data
	
	def restart(self, restfile):
		with open(restfile) as f:
			r = f.readlines()
			for i in range(self.natoms):
				self.sys.rx[i] = float(r[i].split()[0])
				self.sys.ry[i] = float(r[i].split()[1])
				self.sys.rz[i] = float(r[i].split()[2])

			for i in range(self.natoms):
				self.sys.vx[i] = float(r[i+self.natoms].split()[0])
				self.sys.vy[i] = float(r[i+self.natoms].split()[1])
				self.sys.vz[i] = float(r[i+self.natoms].split()[2])

	def go(self):
		for i in range(self.natoms):
			print(self.sys.rx[i])


if __name__ == '__main__':
	input_path = "examples/"+sys.argv[1]
	output_path = "examples/"
	print(input_path)
	so_path = "lib/libljmd.so"
	#input_path = "examples/argon_108.inp"
	main = LJMD(so_path, input_path)
	main.run_simulation()
	#main.go()
