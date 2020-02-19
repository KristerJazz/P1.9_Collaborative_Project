import unittest
from ljmd import *

class LjmdEkinTest(unittest.TestCase):
    def setUp(self):
        so_path = "lib/libljmd.so"
        self.main = LJMD(so_path)

    def test_ekin_value_1(self):
        input_path = "tests/python_tests/test_inputs/test1.inp"
        self.main.initialize_system(input_path)

        self.assertAlmostEqual(0, self.main.sys.ekin, 7)

    def test_ekin_value_2(self):
        input_path = "tests/python_tests/test_inputs/test2.inp"
        self.main.initialize_system(input_path)
        self.assertAlmostEqual(0, self.main.sys.ekin, 7)

    def test_ekin_value_3(self):
        input_path = "tests/python_tests/test_inputs/test3.inp"
        self.main.initialize_system(input_path)
        self.assertAlmostEqual(0, self.main.sys.ekin, 7)

    def test_ekin_value_4(self):
        input_path = "tests/python_tests/test_inputs/test4.inp"
        self.main.initialize_system(input_path)

        self.assertAlmostEqual(0, self.main.sys.ekin, 7)

    def test_ekin_value_5(self):
        input_path = "tests/python_tests/test_inputs/test5.inp"
        self.main.initialize_system(input_path)
        self.assertAlmostEqual(0, self.main.sys.ekin, 7)

    def test_ekin_value_6(self):
        input_path = "tests/python_tests/test_inputs/test6.inp"
        self.main.initialize_system(input_path)
        self.assertAlmostEqual(0, self.main.sys.ekin, 7)

