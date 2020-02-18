import unittest
from ljmd import *

class LjmdForceTest(unittest.TestCase):
    def setUp(self):
        so_path = "lib/libljmd.so"
        self.main = LJMD(so_path)

    def test_force_correct_x(self):
        input_path = "tests/python_tests/test_inputs/test1.inp"
        self.main.initialize_system(input_path)

        self.assertAlmostEqual(1, self.main.sys.fx[0], 7)

    def test_force_correct_y(self):
        input_path = "tests/python_tests/test_inputs/test2.inp"
        self.main.initialize_system(input_path)
        self.assertAlmostEqual(1, self.main.sys.fy[0], 7)

    def test_force_correct_z(self):
        input_path = "tests/python_tests/test_inputs/test3.inp"
        self.main.initialize_system(input_path)
        self.assertAlmostEqual(1, self.main.sys.fz[0], 7)

