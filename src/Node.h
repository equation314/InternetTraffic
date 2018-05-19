#ifndef NODE_H
#define NODE_H

#include <cmath>
#include <vector>
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

struct Node : public Location
{
    Node(int id, double x, double y) : Location(x, y), id(id) {}

    int id;
};

typedef std::vector<const Node*> NodeList;

#endif // NODE_H
