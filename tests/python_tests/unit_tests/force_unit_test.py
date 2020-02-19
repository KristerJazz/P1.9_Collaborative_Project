import unittest
from ctypes import *
from ljmd import MDSYS_T

class LjmdForce2ParticleUnitTest(unittest.TestCase):
    def setUp(self):
        so_path = "lib/libljmd.so"
        self.ljmd = CDLL(so_path)

        self.sys = MDSYS_T(natoms=2,
                           mass=1,
                           epsilon=0.5,
                           sigma=12,
                           rcut=16,
                           box=32,
                           nsteps=1,
                           dt=1)

        self.sys.rx = (c_double * 2)()
        self.sys.ry = (c_double * 2)()
        self.sys.rz = (c_double * 2)()
        self.sys.vx = (c_double * 2)()
        self.sys.vy = (c_double * 2)()
        self.sys.vz = (c_double * 2)()
        self.sys.fx = (c_double * 2)()
        self.sys.fy = (c_double * 2)()
        self.sys.fz = (c_double * 2)()

        """
        For every test, the position and velocity of the two particles
		are initialized to zero.
		Each test will reset some value to a new case
        """
		#Particle 1
        self.sys.rx[0] = 0 
        self.sys.ry[0] = 0
        self.sys.rz[0] = 0
        self.sys.vx[0] = 0
        self.sys.vy[0] = 0
        self.sys.vz[0] = 0

		#Particle 2
        self.sys.rx[1] = 0 
        self.sys.ry[1] = 0
        self.sys.rz[1] = 0
        self.sys.vx[1] = 0
        self.sys.vy[1] = 0
        self.sys.vz[1] = 0

    def test_2_particle_inside_threshold_1(self):
        self.sys.rx[0] = 12

        self.ljmd.force(byref(self.sys))
        self.assertAlmostEqual(1, self.sys.fx[0], 7)
        self.assertAlmostEqual(0, self.sys.fy[0], 7)
        self.assertAlmostEqual(0, self.sys.fz[0], 7)

    def test_2_particle_inside_threshold_2(self):
        self.sys.ry[0] = 12

        self.ljmd.force(byref(self.sys))
        self.assertAlmostEqual(0, self.sys.fx[0], 7)
        self.assertAlmostEqual(1, self.sys.fy[0], 7)
        self.assertAlmostEqual(0, self.sys.fz[0], 7)

    def test_2_particle_inside_threshold_3(self):
        self.sys.rz[0] = 12

        self.ljmd.force(byref(self.sys))
        self.assertAlmostEqual(0, self.sys.fx[0], 7)
        self.assertAlmostEqual(0, self.sys.fy[0], 7)
        self.assertAlmostEqual(1, self.sys.fz[0], 7)

    def test_2_particle_outside_threshold_1(self):
        self.sys.rx[0] = 16

        self.ljmd.force(byref(self.sys))
        self.assertAlmostEqual(0, self.sys.fx[0], 7)
        self.assertAlmostEqual(0, self.sys.fy[0], 7)
        self.assertAlmostEqual(0, self.sys.fz[0], 7)

    def test_2_particle_outside_threshold_2(self):
        self.sys.ry[0] = 16

        self.ljmd.force(byref(self.sys))
        self.assertAlmostEqual(0, self.sys.fx[0], 7)
        self.assertAlmostEqual(0, self.sys.fy[0], 7)
        self.assertAlmostEqual(0, self.sys.fz[0], 7)

    def test_2_particle_outside_threshold_3(self):
        self.sys.rz[0] = 16

        self.ljmd.force(byref(self.sys))
        self.assertAlmostEqual(0, self.sys.fx[0], 7)
        self.assertAlmostEqual(0, self.sys.fy[0], 7)
        self.assertAlmostEqual(0, self.sys.fz[0], 7)
