import unittest

from ljmd import *

class InitTest(unittest.TestCase):
	def test_init_fail(self):
		so = 'io_test.py'
		self.assertRaises(OSError, LJMD, so)
	
	def test_init_fail_no_such_file(self):
		so = 'something_not_existing'
		self.assertRaises(OSError, LJMD, so)
	
	def test_init_success(self):
		so = "lib/libljmd.so"
		print(so)
		LJMD(so)
	
