#ifndef _GPTREE_H
#define _GPTREE_H

#include <vector>

void gptree_build();

int gptree_search(int S, int T);

int gptree_find_path(int S, int T, std::vector<int>& order);

#endif // _GPTREE_H
