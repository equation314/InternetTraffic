import sys
sys.path.insert(0, "..")
from itrafficpy import InternetTraffic
from math import atan2, pi

engine = InternetTraffic('../data/')


def getNearestNode(lon, lat):
    res = engine.get_nearest_node(lon, lat)
    return res


def query(srcId, dstId):
    cars = []
    sols = engine.query(srcId, dstId).result
    for sol in sols:
        car = {
            "location": [sol.car_x, sol.car_y],
            "passengers": list(zip(sol.pass_x, sol.pass_y)),
            "path": list(zip(sol.node_x, sol.node_y)),
            'angle': 90 - atan2(sol.node_y[1] - sol.node_y[0],
                                sol.node_x[1] - sol.node_x[0]) / pi * 180,
            "dis": sol.dis,
            "total_dis": sol.total_dis,
            "detour_dis1": sol.detour_dis1,
            "detour_dis2": sol.detour_dis2,
        }
        cars.append(car)

    return cars
