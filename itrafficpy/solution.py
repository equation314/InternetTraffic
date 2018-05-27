class Solution(object):
    def __init__(self, result):
        self.result = result
        self.parse(result)

    def parse(self, result):
        self.car_id = result[0]
        self.car_x = result[1]
        self.car_y = result[2]

        self.dis = result[3]
        self.total_dis = result[4]
        self.detour_dis1 = result[5]
        self.detour_dis2 = result[6]
        self.value = result[7]

        self.pass_id = result[8]
        self.pass_x = result[9]
        self.pass_y = result[10]
        self.node_id = result[11]
        self.node_x = result[12]
        self.node_y = result[13]

    def print(self):
        print("car #%d(%.2f, %.2f)" % (self.car_id, self.car_x, self.car_y))
        print("\tpassengers: ")
        print("\t", self.pass_id)
        print("\t", self.pass_x)
        print("\t", self.pass_y)
        print("\troute: ")
        print("\t", self.node_x)
        print("\t", self.node_y)
        print("\tdistance to the passenger:            %.2f" % self.dis);
        print("\tdetour distance of passengers on car: %.2f" % self.detour_dis1);
        print("\tdetour distance of current passenger: %.2f" % self.detour_dis2);


class SolutionList(object):
    def __init__(self, res=None):
        self.result = []
        if res is not None:
            for sol in res:
                self.result.append(Solution(sol))
