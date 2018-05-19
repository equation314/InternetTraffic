#include "Car.h"

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

Solution Car::query(const Node* src, const Node* dst) const
{
    if (m_id > 5 || m_passenger_count >= 4) return Solution();
    return Solution(this, m_passengers, 5, 5, 5);
}
