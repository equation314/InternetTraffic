import sys
import os
import platform
import ctypes
from itrafficpy.solution import SolutionList

EXT_NAME = {
    'Darwin': 'dylib',
    'Linux': 'so',
    'Windows': 'dll',
}
ROOT_PATH = os.path.join(os.path.dirname(os.path.realpath(__file__)), '..')


class InternetTraffic(object):
    def __init__(self, data_dir):
        print(os.path.join(ROOT_PATH, 'build', 'itrafficpy',
                           'libitrafficpy.%s' % EXT_NAME[platform.system()]))
        lib = ctypes.cdll.LoadLibrary(
            os.path.join(ROOT_PATH, 'build', 'itrafficpy', 'libitrafficpy.%s' %
                         EXT_NAME[platform.system()]))

        self._get_nearest_node = lib.getNearestNode
        self._get_nearest_node.restype = ctypes.py_object
        self._query = lib.query
        self._query.restype = ctypes.py_object
        self._shutdown = lib.shutdown
        self._lib = lib
        lib.startup(ctypes.create_string_buffer(bytes(data_dir, "ASCII")))

    def __del__(self):
        self._lib.shutdown()

    def get_nearest_node(self, lon, lat):
        PARAM = [ctypes.c_double(num) for num in [lon, lat]]
        res = self._get_nearest_node(*PARAM)
        return res

    def query(self, srcID, dstID):
        res = self._query(srcID, dstID)
        sol = SolutionList(res)
        return sol
