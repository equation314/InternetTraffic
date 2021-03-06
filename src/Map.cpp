#include <cstdio>
#include <assert.h>

#include <GPTree.h>

#include "Map.h"

using namespace std;

Map::Map() {}

Map::~Map()
{
    for (auto node : m_nodes)
        delete node;
    for (auto edge : m_edges)
        delete edge;
}

void Map::load(const string& nodeDataFile, const string& edgeDataFile)
{
    printf("Loading map data...\n");

    m_nodes.clear();
    m_edges.clear();

    FILE* f = fopen(nodeDataFile.c_str(), "r");
    int id, len, a, b;
    double x, y;

    for (int i = 0; fscanf(f, "%d %lf %lf", &id, &x, &y) != EOF; i++)
    {
        assert(i == id);
        m_nodes.push_back(new Node(id, x, y));
    }
    fclose(f);

    f = fopen(edgeDataFile.c_str(), "r");

    fscanf(f, "%d %d", &m_node_count, &m_edge_count);
    while (fscanf(f, "%d %d %d", &a, &b, &len) != EOF)
        m_edges.push_back(new Edge(getNode(a), getNode(b), len));

    fclose(f);
}

const Node* Map::getNearestNode(double x, double y) const
{
    double mi = Const::INF;
    const Node* res = nullptr;
    for (auto node : m_nodes)
    {
        double dis = Location(x, y).earthDistanceTo(node);
        if (dis < mi)
        {
            mi = dis;
            res = node;
        }
    }
    return res;
}

double Map::distance(const Node* a, const Node* b) const
{
    return a->earthDistanceTo(b);
}

double Map::roadmap_distance(const Node* a, const Node* b) const
{
    return gptree_search(a->id, b->id) / 1000.0;
}

void Map::recover_roadmap_path(const Node* a, const Node* b,
                               NodeList& order) const
{
    vector<int> ider;
    gptree_find_path(a->id, b->id, ider);
    for (auto iter = ider.begin(); iter != ider.end(); iter++)
        order.push_back(m_nodes[*iter]);
}
