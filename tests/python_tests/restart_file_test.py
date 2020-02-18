import unittest
from ljmd import *

class RestartTest(unittest.TestCase):
    def setUp(self):
        so_path = "lib/libljmd.so"
        input_path = "examples/argon_108.inp"
        self.main = LJMD(so_path)
        self.main.initialize_system(input_path)

    def test_no_file(self):
        restart_file = "something_non_existent"
        self.assertRaises(FileNotFoundError, self.main.restart, restart_file)

    def test_wrong_input_data1(self):
        restart_file = "examples/argon_108.inp" #wrong input file
        self.assertRaises(AssertionError, self.main.restart, restart_file)

    def test_correct_input(self):
        restart_file = "examples/argon_108.rest"
        self.main.restart(restart_file)
