#ifndef MAP_H
#define MAP_H

#include <string>

#include "Node.h"

struct Edge
{
    Edge(const Node* a, const Node* b, int len) : a(a), b(b), len(len) {}

    const Node *a, *b;
    int len;
};

typedef std::vector<const Edge*> EdgeList;

class Map
{
public:
    Map();
    virtual ~Map();

    const Node* getNode(size_t id) const
    {
        return id >= m_node_count ? nullptr : m_nodes[id];
    }

    const Node* getNearestNode(double x, double y) const;

    double distance(const Node* a, const Node* b) const;

    double roadmap_distance(const Node* a, const Node* b) const;

    void recover_roadmap_path(const Node* a, const Node* b,
                              NodeList& order) const;

    void load(const std::string& nodeDataFile, const std::string& edgeDataFile);

private:
    int m_node_count, m_edge_count;
    NodeList m_nodes;
    EdgeList m_edges;
};

#endif // MAP_H
