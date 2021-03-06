#include "Car.h"
#include "Map.h"

using namespace std;

Car::Car(int id, const Node* pos, const NodeList& passengers)
    : m_id(id), m_passenger_count(passengers.size()), m_pos(pos),
      m_passengers(passengers)
{
}

Car::~Car() {}

void Car::print() const
{
    printf("car #%d: %d %s\n", m_id, m_passenger_count,
           m_pos->toString().c_str());
    printf("\t[ ");
    for (auto node : m_passengers)
        printf("%s, ", node->toString().c_str());
    printf("]\n");
}

double Car::getMinDistance(vector<int>& dstIds, int srcId,
                           const double disMatrix[6][6])
{
    int n = dstIds.size();
    double res = Const::INF;
    vector<int> resList = dstIds;

    if (!n)
        return 0;

    for (int i = 0; i < Const::FACTORIAL[n]; i++)
    {
        vector<int> temp;
        double d = 0;
        for (int j = 0, pred = srcId, j1 = -1, j2 = -1; j < n; j++)
        {
            int now = dstIds[Const::PERMUTATIONS[n][i][j]];
            if (now == 1)
                j1 = j;
            else if (now == 2)
                j2 = j;
            if (j1 >= 0 && j2 >= 0 && j1 > j2)
            {
                d = Const::INF;
                break;
            }

            d += disMatrix[pred][now];
            if (d >= res)
                break;
            temp.push_back(now);
            pred = now;
        }
        if (d < res)
        {
            res = d;
            resList = temp;
        }
    }

    dstIds = resList;
    return res;
}

bool Car::earthDistanceCheck(const Node* src, const Node* dst,
                             const Map* map) const
{
    if (m_passenger_count >= 4)
        return false;

    double d2 = map->distance(m_pos, src);
    return d2 <= 10;
}

Solution Car::query(const Node* src, const Node* dst, const Map* map) const
{
    if (!earthDistanceCheck(src, dst, map))
        return Solution();

    NodeList nodes = {m_pos, src, dst};
    for (auto node : m_passengers)
        nodes.push_back(node);

    double disMatrix[6][6];
    memset(disMatrix, 0, sizeof(disMatrix));
    for (int i = 0; i < nodes.size(); i++)
        for (int j = 0; j < i; j++)
        {
            disMatrix[i][j] = disMatrix[j][i] =
                map->roadmap_distance(nodes[i], nodes[j]);
            if (disMatrix[0][1] > 10)
                return Solution();
        }

    double d2 = disMatrix[0][1];
    double d4 = disMatrix[1][2];

    /* car: 0
     * src: 1
     * dst: 2
     */
    vector<int> dstIds;
    for (int i = 0; i < m_passengers.size(); i++)
        dstIds.push_back(i + 3);

    double d1 = getMinDistance(dstIds, 0, disMatrix);

    dstIds.push_back(1);
    dstIds.push_back(2);
    double d5 = getMinDistance(dstIds, 0, disMatrix);

    double detour_dis1 = d5 - d1;
    double detour_dis2 = -d4;

    // current passenge is arrived
    int srcId = 0;
    double car_dis = 0;
    for (auto i : dstIds)
    {
        car_dis += disMatrix[i][srcId];
        srcId = i;

        if (i == 1)
            detour_dis2 -= car_dis;
        else if (i == 2)
            break;
    }
    detour_dis2 += car_dis;
    // printf("#%d %s %s %s\n", m_id, m_pos->toString().c_str(),
    //        src->toString().c_str(), dst->toString().c_str());
    // printf("\t d1=%lf d2=%lf d3=%lf d4=%lf d3'=%lf\n", d1, d2, d3, d4,
    //        detour_dis2 + d4);

    if (detour_dis1 > 10 || detour_dis2 > 10)
        return Solution();

    NodeList path = {m_pos};
    for (auto i : dstIds)
    {
        if (i == 1)
            path.push_back(src);
        else if (i == 2)
            path.push_back(dst);
        else
            path.push_back(m_passengers[i - 3]);
    }

    return Solution(this, path, d2, detour_dis2 + d4, detour_dis1, detour_dis2,
                    car_dis);
}
