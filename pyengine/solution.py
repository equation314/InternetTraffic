class SingleSolution(object):
    def __init__(self, result):
        self.parse(result)

    def parse(self, result):
        self.car_id = result[0]
        self.car_x  = result[1]
        self.car_y  = result[2]

        self.dis         = result[3]
        self.detour_dis1 = result[4]
        self.detour_dis2 = result[5]
        self.value       = result[6]

        self.node_id    = result[7]
        self.node_x     = result[8]
        self.node_y     = result[9]
    
    def print(self):
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