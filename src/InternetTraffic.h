#ifndef INTERNET_TRAFFIC_H
#define INTERNET_TRAFFIC_H

#include <string>
#include <vector>

#include "Car.h"
#include "Map.h"

class InternetTraffic
{
public:
    InternetTraffic();
    virtual ~InternetTraffic();

    void startup(const std::string& dataDir);

private:
    Map* m_map;
    std::vector<Car*> m_cars;

    void loadCars(const std::string& dataFile);
};

#endif // INTERNET_TRAFFIC_H
