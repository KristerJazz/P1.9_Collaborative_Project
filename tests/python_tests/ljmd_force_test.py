import unittest
from ljmd import *

class LjmdForceTest(unittest.TestCase):
    def setUp(self):
        so_path = "lib/libljmd.so"
        self.main = LJMD(so_path)

    def test_force_correct(self):
        input_path = "examples/argon_108.inp"
        self.main.initialize_system(input_path)
        print(self.main.sys.fx[0])
        raise
	

    def test_force_correct_0_outside_1(self):
        correct_force = 0
        #assert(self.main.sys
