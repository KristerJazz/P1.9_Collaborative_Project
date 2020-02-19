import unittest
from ljmd import *
import os

class SystemInitTest(unittest.TestCase):
    def setUp(self):
        so_path = "lib/libljmd.so"
        self.main = LJMD(so_path)
        os.environ["EXAMPLES_PATH"] = "tests/python_tests/test_inputs/"

    def test_initialize_system_correct(self):
        correct_file = "tests/python_tests/test_inputs/test1.inp"
        self.main.initialize_system(correct_file)

    def test_wrong_input_values(self):
        wrong_data_in_file = "tests/python_tests/test_inputs/wrong_input.inp"
        self.assertRaises(ValueError, self.main.initialize_system, wrong_data_in_file)
