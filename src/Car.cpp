#include "Car.h"
#include "Map.h"

using namespace std;

const int FACTORIAL[5] = {1, 1, 2, 6, 24};
const int PERMUTATIONS[5][24][4] = {
    {},
    {{0}},
    {{0, 1}, {1, 0}},
    {{0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 0, 1}, {2, 1, 0}},
    {
        {0, 1, 2, 3}, {0, 1, 3, 2}, {0, 2, 1, 3}, {0, 2, 3, 1}, {0, 3, 1, 2},
        {0, 3, 2, 1}, {1, 0, 2, 3}, {1, 0, 3, 2}, {1, 2, 0, 3}, {1, 2, 3, 0},
        {1, 3, 0, 2}, {1, 3, 2, 0}, {2, 0, 1, 3}, {2, 0, 3, 1}, {2, 1, 0, 3},
        {2, 1, 3, 0}, {2, 3, 0, 1}, {2, 3, 1, 0}, {3, 0, 1, 2}, {3, 0, 2, 1},
        {3, 1, 0, 2}, {3, 1, 2, 0}, {3, 2, 0, 1}, {3, 2, 1, 0},
    },
};

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
    int n = list.size();
    double res = Const::INF;
    NodeList resList = list;
    vector<int> a;

    if (!n)
        return 0;

    for (int i = 0; i < FACTORIAL[n]; i++)
    {
        NodeList temp = list;
        for (int j = 0; j < n; j++)
            temp[j] = list[PERMUTATIONS[n][i][j]];
        double d = getDistanceByOrder(temp, src, map);

        if (d < res)
        {
            res = d;
            resList = temp;
        }
    }

    list = resList;
    return res;
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

    double detour_dis1 = d2 + d3 - d1;
    double detour_dis2 = -d4;

    // current passenge is arrived
    for (auto node : order)
    {
        detour_dis2 += map->distance(src, node);
        src = node;
        if (node->id == dst->id)
            break;
    }

    // printf("#%d %s %s %s\n", m_id, m_pos->toString().c_str(),
    //        src->toString().c_str(), dst->toString().c_str());
    // printf("\t d1=%lf d2=%lf d3=%lf d4=%lf d3'=%lf\n", d1, d2, d3, d4,
    //        detour_dis2 + d4);

    if (detour_dis1 > 10 || detour_dis2 > 10)
        return Solution();

    return Solution(this, order, d2, detour_dis1, detour_dis2);
}
