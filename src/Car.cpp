#include "Car.h"
#include "Map.h"

Car::Car(int id, const Node* pos, const NodeList& passengers)
    : m_id(id), m_passenger_count(passengers.size()), m_pos(pos),
      m_passengers(passengers)
{
}

Car::~Car()
{
}

void Car::print() const
{
    printf("car #%d: %d %s\n", m_id, m_passenger_count,
           m_pos->toString().c_str());
    printf("\t[ ");
    for (auto node : m_passengers)
        printf("%s, ", node->toString().c_str());
    printf("]\n");
}

double Car::getDistanceByOrder(const NodeList& list, const Node* src,
                               const Map* map)
{
    double d = 0;
    const Node* pred = src;
    for (auto node : list)
    {
        d += map->distance(pred, node);
        pred = node;
    }
    return d;
}

double Car::getMinDistance(NodeList& list, const Node* src, const Map* map)
{
    return getDistanceByOrder(list, src, map);
}

Solution Car::query(const Node* src, const Node* dst, const Map* map) const
{
    if (m_passenger_count >= 4)
        return Solution();

    double d2 = map->distance(m_pos, src);
    if (d2 > 10)
        return Solution();

    double d4 = map->distance(src, dst);

    NodeList order = m_passengers;
    double d1 = getMinDistance(order, m_pos, map);

    order.push_back(dst);
    double d3 = getMinDistance(order, src, map);

    // printf("#%d %s %s %s\n", m_id, m_pos->toString().c_str(),
    //        src->toString().c_str(), dst->toString().c_str());
    // printf("\t d1=%lf d2=%lf d3=%lf d4=%lf\n", d1, d2, d3, d4);

    double detour_dis1 = d2 + d3 - d1;
    double detour_dis2 = d3 - d4;
    if (detour_dis1 > 10 || detour_dis2 > 10)
        return Solution();

    return Solution(this, order, d2, detour_dis1, detour_dis2);
}
