#include <cstdio>

#include "Car.h"
#include "Solution.h"

void Solution::print() const
{
    printf("car #%d%s:\n", car->getId(), car->getPos()->toString().c_str());

    printf("\tarrival order:");
    for (auto node : order)
        printf(" %s", node->toString().c_str());
    printf("\n");

    printf("\tdistance to the passenger:            %.6lf\n", dis);
    printf("\tdetour distance of passengers on car: %.6lf\n", detour_dis1);
    printf("\tdetour distance of current passenger: %.6lf\n", detour_dis2);
}
