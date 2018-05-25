#ifndef SOLUTION_H
#define SOLUTION_H

#include "Const.h"
#include "Node.h"

class Car;

struct Solution
{
    Solution() : dis(Const::INF) {}
    Solution(const Car* car, const NodeList& path, double dis, double total_dis,
             double detour_dis1, double detour_dis2, double value)
        : car(car), path(path), dis(dis), total_dis(total_dis),
          detour_dis1(detour_dis1), detour_dis2(detour_dis2),
          value(value)
    {
    }

    const Car* car;
    NodeList path;

    double dis;         // distance between the car and current passenger
    double total_dis;   // total distance from src to dst
    double detour_dis1; // detour distance of passengers alreay on the car
    double detour_dis2; // detour distance of current passenger

    double value;

    void print() const;

    bool isOk() const { return dis <= 10; }

    bool operator<(const Solution& sol) const
    {
        return value < sol.value ||
               (value == sol.value && detour_dis1 < sol.detour_dis1);
    }
};

typedef std::vector<Solution> SolutionList;

#endif // SOLUTION_H
