#ifndef SOLUTION_H
#define SOLUTION_H

#include "Const.h"
#include "Node.h"

class Car;

struct Solution
{
    Solution() : dis(Const::INF) {}
    Solution(const Car* car, const NodeList& order, double dis,
             double detour_dis1, double detour_dis2)
        : car(car), order(order), dis(dis), detour_dis1(detour_dis1),
          detour_dis2(detour_dis2)
    {
    }

    const Car* car;
    NodeList order; // arrival order

    double dis;         // distance between the car and current passenger
    double detour_dis1; // detour distance of passengers alreay on the car
    double detour_dis2; // detour distance of current passenger

    void print() const;

    bool isOk() const { return dis <= 10; }
};

typedef std::vector<const Solution> SolutionList;

#endif // SOLUTION_H
