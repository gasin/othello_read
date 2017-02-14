#include "global.h"

#ifndef HASH_H
#define HASH_H

extern unordered_map<ull, int> hash_table;
extern ull random_number[RANDOM_NUMBER];

void init_random();
ull make_hash(ull black, ull white, bool now);

#endif
