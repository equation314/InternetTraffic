#include "InternetTraffic.h"

int main()
{
    InternetTraffic* engine = new InternetTraffic();
    engine->startup();
    delete engine;
    return 0;
}
