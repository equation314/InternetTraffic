#include "InternetTraffic.h"

int main()
{
    InternetTraffic* engine = new InternetTraffic();
    engine->startup("../data");
    delete engine;
    return 0;
}
