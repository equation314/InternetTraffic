import sys
sys.path.insert(0, "..")
import pyengine

pyengine.init('../data')


def getNearestNode(lon, lat):
    res = pyengine.get_node_in_map(lon, lat)
    return res


def query(srcId, dstId):
    sols = pyengine.search_id(2333, 2334)
    print(sols)
