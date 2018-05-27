#include <algorithm>
#include <cstdio>
#include <ctime>
#include <assert.h>

#include <GPTree.h>

#include "InternetTraffic.h"

using namespace std;

const char CAR_DATA[] = "car.txt";
const char NODE_DATA[] = "road.cnode";
const char EDGE_DATA[] = "road.nedge";

InternetTraffic::InternetTraffic() : m_map(new Map()) {}

InternetTraffic::~InternetTraffic()
{
    delete m_map;
    for (auto car : m_cars)
        delete car;
}

void InternetTraffic::loadCars(const string& dataFile)
{
    printf("Loading cars data...\n");

    m_cars.clear();

    FILE* f = fopen(dataFile.c_str(), "r");

    int id, n, nodeId;
    double x, y;
    for (int i = 0;
         fscanf(f, "%d %d %lf,%lf,%d", &id, &n, &x, &y, &nodeId) != EOF; i++)
    {
        assert(i == id);

        const Node* node = m_map->getNode(nodeId);
        assert(node != nullptr && node->x == x && node->y == y);

        NodeList passengers;
        for (int j = 0; j < n; j++)
        {
            fscanf(f, "%lf,%lf,%d", &x, &y, &nodeId);
            const Node* node = m_map->getNode(nodeId);
            assert(node != nullptr && node->x == x && node->y == y);
            passengers.push_back(node);
        }

        Car* car = new Car(id, node, passengers);
        m_cars.push_back(car);
    }
    fclose(f);
}

void InternetTraffic::startup(const string& dataDir)
{
    printf("Internet traffic system is starting...\n");

    m_map->load(dataDir + "/" + NODE_DATA, dataDir + "/" + EDGE_DATA);
    loadCars(dataDir + "/" + CAR_DATA);

    gptree_build((dataDir + "/").c_str());
}

SolutionList InternetTraffic::query(const Node* src, const Node* dst)
{
    printf("Current passenger's route: %s -> %s\n", src->toString().c_str(),
           dst->toString().c_str());

    int begin_time = clock();

    vector<double> dis(m_cars.size());
    vector<int> ids;

    SolutionList all, res;
    for (int i = 0; i < m_cars.size(); i++)
    {
        auto car = m_cars[i];
        if (m_map->distance(src, car->getPos()) <= 10)
        {
            double d = m_map->roadmap_distance(src, car->getPos());
            if (d <= 10)
            {
                dis[i] = d;
                ids.push_back(i);
            }
        }
    }
    sort(ids.begin(), ids.end(), [&](int a, int b) { return dis[a] < dis[b]; });

    for (auto id : ids)
    {
        auto car = m_cars[id];
        Solution sol = car->query(src, dst, m_map);
        if (sol.isOk())
            all.push_back(sol);
        if (all.size() >= 200)
            break;

        if (1.0 * (clock() - begin_time) / CLOCKS_PER_SEC > 8)
            break;
    }
    printf("%d\n", (int) all.size());
    sort(all.begin(), all.end());

    for (int i = 0; i < 5 && i < all.size(); i++)
    {
        NodeList path;
        for (int j = 0; j < all[i].path.size() - 1; j++)
            m_map->recover_roadmap_path(all[i].path[j], all[i].path[j + 1],
                                        path);

        all[i].path = path;
        res.push_back(all[i]);
    }
    printf("OK, found %d solutions.\n", (int) res.size());

    return res;
}
