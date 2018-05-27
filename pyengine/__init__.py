"""
Python wrapper for C++ backend.
Usage:
1. call init(dir) with the dir of the data
2. call search_id(srcID, dstID) to get the solution. The return type is defined in `solution.py`.
3. call destroy() if all the query are finished.
"""
import sys, platform
sys.path.insert(0, "pyengine")
import ctypes
from solution import SolutionList

EXT_NAME = {
    'Darwin': 'dylib',
    'Linux': 'so',
    'Windows': 'dll',
}
lib = ctypes.cdll.LoadLibrary("build/src/libengine.%s" % EXT_NAME[platform.system()])

engine_search_id_ = lib.search_id
engine_search_id_.restype = ctypes.py_object
engine_search_xy_ = lib.search_xy
engine_search_xy_.restype = ctypes.py_object
engine_get_node_in_map_ = lib.get_node_in_map
engine_get_node_in_map_.restype = ctypes.py_object

# init
def init(dir):
    return lib.init(ctypes.create_string_buffer(bytes(dir, "ASCII")))

def destroy():
    return lib.destroy()

def search_id(srcID, dstID):
    res = engine_search_id_(srcID, dstID)
    sol = SolutionList(res)
    sol.parse()
    return sol

def search_xy(st_x, st_y, ed_x, ed_y):
    PARAM = [ctypes.c_double(num) for num in [st_x, st_y, ed_x, ed_y]]
    res = engine_search_xy_(*PARAM)
    sol = SolutionList(res)
    sol.parse()
    return sol

def get_node_in_map(x, y):
    PARAM = [ctypes.c_double(num) for num in [x, y]]
    res = engine_get_node_in_map_(*PARAM)
    return res


def test():
    print("Test init")
    init("data")
    print("Test get nearest point on map")
    res = get_node_in_map(110.0, 40.5)
    print(res)
    print("Test search id")
    sol = search_id(2333, 2334)
    print("Test search (x,y)")
    sol = search_xy(110.0, 40.5, 110.2, 40.7)
    print("Test destory")
    destroy()
    print("Done")
