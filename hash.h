#include "global.h"

#ifndef HASH_H
#define HASH_H

extern unordered_map<ull, int> hash_table;
extern ull random_number[RANDOM_NUMBER];
extern ull hash_mask[8][(1<<8)][2];

void init_random();
ull make_hash(ull me, ull op);

#endif
