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

    /// Get the nearest node by (x, y)
    const Node* getNode(double x, double y) const {
        int i;
        double mini = 0xffffff, dist= 0xffffff;
        const Node *res = NULL, *cur = NULL;
        for(i = 0; i < m_nodes.size(); i++) {
            cur = m_nodes[i];
            dist = (x - cur->x) * (x - cur->x) + (y - cur->y) * (y - cur->y);
            //dist = (x - cur.x) * (x - cur.x) + (y - cur.y) * (y - cury);
            if(mini > dist) {
                mini = dist;
                res = cur;
            }
        }
        return res;
    }

    const Node* getNode(size_t id) const
    {
        return id >= m_node_count ? nullptr : m_nodes[id];
    }

    double distance(const Node* a, const Node* b) const;

    void load(const std::string& nodeDataFile, const std::string& edgeDataFile);

private:
    int m_node_count, m_edge_count;
    NodeList m_nodes;
    EdgeList m_edges;
};

#endif // MAP_H
