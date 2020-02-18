from ctypes import *
import os

if __name__ == '__main__':
    so_path = "./libhello.so"
    rank = os.environ["OMPI_COMM_WORLD_RANK"]
    hello_func = CDLL(so_path)
    hello_func.init()
    if rank == "0":
        print("Just master")
        hello_func.hello()
        print("All")
    hello_func.hello()
    hello_func.finalise()
