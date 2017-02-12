#include "global.h"

#ifndef CHANGE_BOARD_H
#define CHANGE_BOARD_H

bool unhash_change_board(bitset<64>& black, bitset<64>& white, bool now, int h, int w);
bool hash_change_board(bitset<64>& black, bitset<64>& white, bool now, int h, int w, ll& hasher);

#endif
