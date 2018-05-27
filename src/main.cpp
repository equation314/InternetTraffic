#include "InternetTraffic.h"

int main()
{
    InternetTraffic* engine = new InternetTraffic();

    engine->startup("../data");

    double srcLon = 117.08276, srcLat = 39.95343;
    double dstLon = 117.08538, dstLat = 39.95314;
    const Node* src = engine->getMap()->getNearestNode(srcLon, srcLat);
    const Node* dst = engine->getMap()->getNearestNode(dstLon, dstLat);
    SolutionList res = engine->query(src, dst);

    for (auto sol : res)
        sol.print();

    delete engine;

    return 0;
}
