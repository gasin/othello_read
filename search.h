#include "global.h"
#ifndef SEARCH_H
#define SEARCH_H

int black_final_search(ull& black, ull& white, int h, int w);
int white_final_search(ull& black, ull& white, int h, int w);
int unhash_search(ull black, ull white, int empty[EMPTY_AREA+1], bool now, bool suc);
int hash_search(ull black, ull white, int empty[EMPTY_AREA+1], bool now, bool suc, ll hasher, int depth);
int firstsearch(ull black, ull white, bool now);

#endif
