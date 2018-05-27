#ifndef MAP_H
#define MAP_H

#include <string>

#include "Node.h"

/// These functions are defined in GPTree
extern int tree_search(int S, int T);
extern void tree_setup();
extern int tree_find_path(int S, int T, std::vector<int> &order);

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
        double mini = 10000000.0, dist= 10000000.0;
        const Node *res = NULL, *cur = NULL;
        for(i = 0; i < m_nodes.size(); i++) {
            cur = m_nodes[i];
            dist = ((x - cur->x)) * ((x - cur->x));
            dist +=((y - cur->y)) * ((y - cur->y));

            //dist = (x - cur.x) * (x - cur.x) + (y - cur.y) * (y - cury);
            if(mini > dist) {
                mini = dist;
                res = cur;
            }
        }
        //printf("%.10lf\n", mini);
        //printf("%.10lf, %.10lf\n", res->x, res->y);
        return res;
    }

    const Node* getNode(size_t id) const
    {
        return id >= m_node_count ? nullptr : m_nodes[id];
    }

    double distance(const Node* a, const Node* b) const;

    int roadmap_distance(const Node *a, const Node *b) const;

    int recover_roadmap_path(const Node *a, const Node *b, std::vector<const Node*> &order) const;

    void load(const std::string& nodeDataFile, const std::string& edgeDataFile);

private:
    int m_node_count, m_edge_count;
    NodeList m_nodes;
    EdgeList m_edges;
};

#endif // MAP_H
