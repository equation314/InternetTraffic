#ifndef INTERNET_TRAFFIC_H
#define INTERNET_TRAFFIC_H

#include <string>

#include "Car.h"
#include "Map.h"
#include "Solution.h"

class InternetTraffic
{
public:
    InternetTraffic();
    virtual ~InternetTraffic();

    const Map* getMap() const { return m_map; }

    void startup(const std::string& dataDir);

    SolutionList query(const Node* src, const Node* dst);

private:
private:
    Map* m_map;
    CarList m_cars;

    void loadCars(const std::string& dataFile);
};

#endif // INTERNET_TRAFFIC_H
