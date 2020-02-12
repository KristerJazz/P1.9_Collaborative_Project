from ctypes import *

so_file = "Obj-serial/ljmd.o"

my_functions = CDLL(so_file)
