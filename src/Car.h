#ifndef CAR_H
#define CAR_H

#include "Location.h"
#include "Map.h"

struct Car
{
public:
    Car(int id, const Node* pos, const NodeList& passengers);
    virtual ~Car();

    void print() const;

private:
    int m_id, m_passenger_count;
    const Node* m_pos;
    std::vector<const Node*> m_passengers;
};

#endif // CAR_H
