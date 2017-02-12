#include "global.h"

#ifndef HASH_H
#define HASH_H

struct HASH_DATA{
    P board;
    int val;
};
extern unordered_map<int, vector<HASH_DATA>> hash_table;
extern int random_number[RANDOM_NUMBER];

void init_random();
P make_board(bitset<64> black, bitset<64> white, bool now);
int make_hash(bitset<64> black, bitset<64> white, bool now);

#endif
