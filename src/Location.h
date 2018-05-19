#ifndef LOCATION_H
#define LOCATION_H

#include <cmath>
#include <string>

struct Location
{
    Location(double x, double y) : x(x), y(y) {}

    double x, y;

    double distanceTo2(const Location& loc) const
    {
        return (x - loc.x) * (x - loc.x) + (y - loc.y) * (y - loc.y);
    }

    double distanceTo(const Location& loc) const
    {
        return sqrt(distanceTo2(loc));
    }

    std::string toString() const;
};

#endif // LOCATION_H
