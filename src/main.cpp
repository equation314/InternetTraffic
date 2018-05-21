#include "InternetTraffic.h"

extern void tree_search(int S, int T);
extern void tree_setup();

int main()
{
    tree_setup();

    InternetTraffic* engine = new InternetTraffic();

    engine->startup("../data");

    int srcId = 2333, dstId = 2334;
    const Node* src = engine->getMap()->getNode(srcId);
    const Node* dst = engine->getMap()->getNode(dstId);
    SolutionList res = engine->query(src, dst);

    for (auto sol : res)
        sol.print();

    delete engine;


    return 0;
}
