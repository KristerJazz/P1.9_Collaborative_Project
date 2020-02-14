import unittest
from ljmd import *

class IOtest(unittest.TestCase):
	def test_success(self):
		assert(5==5)

	def test_fail(self):
		assert(5==4)
	#def setUp(self):
	#	self.testfile = open("examples/argon_108.inp")
	#	print(self.testfile)

		
