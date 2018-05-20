class SingleSolution(object):
    def __init__(self, result):
        self.result = result
        self.parse(result)

    def parse(self, result):
        cnt = 0
        self.car_id = result[cnt]; cnt += 1
        self.car_x  = result[cnt]; cnt += 1
        self.car_y  = result[cnt]; cnt += 1
        self.pass_id= result[cnt]; cnt += 1

        self.dis         = result[cnt]; cnt += 1
        self.detour_dis1 = result[cnt]; cnt += 1
        self.detour_dis2 = result[cnt]; cnt += 1
        self.value       = result[cnt]; cnt += 1

        self.node_id    = result[cnt]; cnt += 1
        self.node_x     = result[cnt]; cnt += 1
        self.node_y     = result[cnt]; cnt += 1
    
    def print(self):
        print("Car %d at (%.2f, %.2f)" % (self.car_id, self.car_x, self.car_y))
        print("Passenger ID: ")
        print(self.pass_id)
        print("Route: ")
        print(self.node_x)
        print(self.node_y)


class Solution(object):
    """
    Parse from raw PyObject Result
    """
    def __init__(self, result=None):
        self.raw_result = result
    
    def parse(self):
        self.result = []
        for single in self.raw_result:
            self.result.append(SingleSolution(single))
            self.result[-1].print()