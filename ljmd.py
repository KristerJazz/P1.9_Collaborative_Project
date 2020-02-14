from ctypes import *

so_files = "lib/libljmd.so"

my_functions = CDLL(so_files)
print(my_functions)
