#include "global.h"
#ifndef SEARCH_H
#define SEARCH_H

bool change_board(bitset<64>& black, bitset<64>& white, bool now, int h, int w);
int black_final_search(bitset<64>& black, bitset<64>& white, int h, int w);
int white_final_search(bitset<64>& black, bitset<64>& white, int h, int w);
int search(bitset<64> black, bitset<64> white, int empty[EMPTY_AREA+1], bool now, bool suc);
int firstsearch(bitset<64> black, bitset<64> white, bool now);

#endif
