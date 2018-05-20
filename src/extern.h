#ifndef EXTERN_H_
#define EXTERN_H_

#include <cstdio>
#include <assert.h>
#include <cstring>
#include <Python.h>
#include "InternetTraffic.h"

extern "C" {

void test_python();

PyObject* getList(){
  PyObject *PList = PyList_New(0);

  std::vector <int> intVector;
  std::vector<int>::const_iterator it;

  for(int i = 0 ; i < 10 ; i++){
    intVector.push_back(i);
  }

  for(it = intVector.begin(); it != intVector.end() ; it++ ){
    PyList_Append(PList, Py_BuildValue("i", *it));
  }

  return PList;
}

InternetTraffic* engine  = NULL;

int init(const char *dir) {
    
    if(engine != NULL) {
        printf("[!] Already initialized!\n");
        return -1;
    }

    engine = new InternetTraffic();
    printf("Dir: %s\n", dir);
    engine->startup(dir);

    return 0;
}

PyObject* search(int srcID, int dstID) {
    PyObject *ret = PyList_New(0);

    const Node* src = engine->getMap()->getNode(srcID);
    const Node* dst = engine->getMap()->getNode(dstID);
    SolutionList res = engine->query(src, dst);

    for (auto sol : res) {
        PyObject *single_sol = PyList_New(0);
        PyObject *node_x = PyList_New(0);
        PyObject *node_y = PyList_New(0);
        PyObject *node_id = PyList_New(0);

        // add car id
        PyList_Append(single_sol, Py_BuildValue("i", sol.car->getId()));

        // add car x&y
        PyList_Append(single_sol, Py_BuildValue("i", sol.car->getPos()->x));
        PyList_Append(single_sol, Py_BuildValue("i", sol.car->getPos()->y));
        
        for(auto iter = sol.order.begin(); iter != sol.order.end(); iter++) {
            PyList_Append(node_id, Py_BuildValue("i", (*iter)->id));
            PyList_Append(node_x, Py_BuildValue("d",  (*iter)->x));
            PyList_Append(node_y, Py_BuildValue("d",  (*iter)->y));
        }

        PyList_Append(single_sol, Py_BuildValue("d", sol.dis        ));
        PyList_Append(single_sol, Py_BuildValue("d", sol.detour_dis1));
        PyList_Append(single_sol, Py_BuildValue("d", sol.detour_dis2));
        PyList_Append(single_sol, Py_BuildValue("d", sol.value      ));

        PyList_Append(single_sol, node_id   );
        PyList_Append(single_sol, node_x    );
        PyList_Append(single_sol, node_y    );

        PyList_Append(ret, single_sol);
    }
    return ret;
}

int destroy() {
    if(engine == NULL) {
        printf("[!] Not initialized!\n");
        return -1;
    }

    delete engine;
    engine = NULL;

    return 0;
}

// test functions

int set_argument(char *s) {
    memcpy(s, "here", 4);
}


}

#endif