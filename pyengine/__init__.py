"""
Python wrapper for C++ backend.
Usage:
1. call init(dir) with the dir of the data
2. call search_id(srcID, dstID) to get the solution. The return type is defined in `solution.py`.
3. call destroy() if all the query are finished.
"""
import sys
sys.path.insert(0, "pyengine")
import ctypes
from solution import Solution

lib = ctypes.cdll.LoadLibrary("build/src/libengine.so")   

engine_search_id_ = lib.search
engine_search_id_.restype = ctypes.py_object

# init
def init(dir):
    return lib.init(ctypes.create_string_buffer(bytes(dir, "ASCII")))

def destroy():
    return lib.destroy()

def search_id(srcID, dstID):
    res = engine_search_id_(srcID, dstID)
    sol = Solution(res)
    sol.parse()
    return sol


def test():
    print("Test init")
    init("data")
    print("Test search")
    sol = search_id(2333, 2334)
    print("Test destory")
    destroy()
    print("Done")
