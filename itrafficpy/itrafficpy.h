#ifndef _ITRAFFIC_PY_H
#define _ITRAFFIC_PY_H

#include <cstdio>
#include <cstring>
#include <Python.h>
#include <assert.h>

#include <InternetTraffic.h>

extern "C"
{
    int init(const char* dir);

    PyObject* get_node_in_map(double x, double y);

    PyObject* search_xy(double st_x, double st_y, double ed_x, double ed_y);

    PyObject* search_id(int srcID, int dstID);

    int destroy();
}

#endif // _ITRAFFIC_PY_H
