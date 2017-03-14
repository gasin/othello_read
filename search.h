#ifndef SEARCH_H
#define SEARCH_H

#include "global.h"

int flip_count(int pos, ull me, ull op);
int how_many_canput(ull me, ull op, int empty[EMPTY_AREA+1]);
int final_search(ull me, ull op, int z);
int unhash_search(ull me, ull op, int empty[EMPTY_AREA+1], bool suc);
int hash_search(ull me, ull op, int empty[EMPTY_AREA+1], bool suc, int depth);
int firstsearch(ull me, ull op);

#endif
