import sys
sys.path.insert(0, "..")
import pyengine

pyengine.init('../data')


def getNearestNode(lon, lat):
    res = pyengine.get_node_in_map(lon, lat)
    return res


def query(srcId, dstId):
    cars = []
    sols = pyengine.search_id(srcId, dstId)
    for sol in sols.result:
        car = {
            "location": [sol.car_x, sol.car_y],
            "passengers": list(zip(sol.pass_x, sol.pass_y)),
            "path": list(zip(sol.node_x, sol.node_y)),
            "dis": sol.dis,
            "detour_dis1": sol.detour_dis1,
            "detour_dis2": sol.detour_dis2,
        }
        cars.append(car)

    return cars
