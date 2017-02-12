#include "hash.h"

unordered_map<ll, int> hash_table;
ll random_number[RANDOM_NUMBER];

void init_random(){
	mt19937_64 mt(114514);
    for(int i = 0; i < RANDOM_NUMBER; i++){
        random_number[i] = mt();
        if(random_number[i] < 0) random_number[i] *= -1;
    }
}

ll make_hash(bitset<64> black, bitset<64> white, bool now){
    ll ret = 0;
    int pointer = 0;
    rep(i,64){
        if(black[i]) ret ^= random_number[pointer];
        else if(white[i]) ret ^= random_number[pointer+1];
        pointer += 2;
    }
    if(now) ret ^= random_number[pointer];
    return ret;
}

