#ifndef _ITRAFFIC_PY_H
#define _ITRAFFIC_PY_H

#include <cstdio>
#include <cstring>
#include <Python.h>
#include <assert.h>

#include <InternetTraffic.h>

extern "C"
{
    int startup(const char* dir);

    PyObject* getNearestNode(double x, double y);

    PyObject* query(int srcID, int dstID);

    int shutdown();
}

#endif // _ITRAFFIC_PY_H
