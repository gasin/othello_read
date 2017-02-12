#include "global.h"
#ifndef SEARCH_H
#define SEARCH_H

int black_final_search(bitset<64>& black, bitset<64>& white, int h, int w);
int white_final_search(bitset<64>& black, bitset<64>& white, int h, int w);
int unhash_search(bitset<64> black, bitset<64> white, int empty[EMPTY_AREA+1], bool now, bool suc);
int hash_search(bitset<64> black, bitset<64> white, int empty[EMPTY_AREA+1], bool now, bool suc, ll hasher, int depth);
int firstsearch(bitset<64> black, bitset<64> white, bool now);

#endif
