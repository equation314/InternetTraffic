#ifndef CAR_H
#define CAR_H

#include "Node.h"
#include "Solution.h"

class Map;

class Car
{
public:
    Car(int id, const Node* pos, const NodeList& passengers);
    virtual ~Car();

    int getId() const { return m_id; }

    const Node* getPos() const { return m_pos; }

    void print() const;

    Solution query(const Node* src, const Node* dst, const Map* map) const;

private:
    int m_id, m_passenger_count;
    const Node* m_pos;
    NodeList m_passengers;

    static double getDistanceByOrder(const NodeList& list, const Node* src,
                                     const Map* map);

    static double getMinDistance(NodeList& list, const Node* src,
                                 const Map* map);
};

typedef std::vector<const Car*> CarList;

#endif // CAR_H
