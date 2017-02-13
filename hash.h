#include "global.h"

#ifndef HASH_H
#define HASH_H

extern unordered_map<ll, int> hash_table;
extern ll random_number[RANDOM_NUMBER];

void init_random();
ll make_hash(ull black, ull white, bool now);

#endif
