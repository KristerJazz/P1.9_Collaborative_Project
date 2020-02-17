import unittest
from ljmd import *


class IOtest(unittest.TestCase):
	def setUp(self):
		so_path = "lib/libljmd.so"
		self.main = LJMD(so_path)

	def test_no_file(self):
		input_file = "something_non_existent"
		self.assertRaises(FileNotFoundError, self.main.read_input, input_file)
	
	def test_wrong_input_data1(self):
		input_file = "examples/argon_108.rest"
		self.assertRaises(AssertionError, self.main.read_input, input_file)
