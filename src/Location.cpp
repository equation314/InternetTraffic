#include <cstdio>

#include "Location.h"

std::string Location::toString() const
{
    char buf[256];
    sprintf(buf, "(%lf, %lf)", x, y);
    return buf;
}
