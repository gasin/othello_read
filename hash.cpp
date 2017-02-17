#include "hash.h"

unordered_map<ull, int> hash_table;
ull random_number[RANDOM_NUMBER];
ull hash_mask[8][(1<<8)][2];

void init_random(){
	mt19937_64 mt(114513);
    for(int i = 0; i < RANDOM_NUMBER; i++){
        random_number[i] = mt();
    }
    memset(hash_mask,0,sizeof(hash_mask));
    rep(i,8) rep(j,(1<<8)){
        rep(u,8) rep(k,2){
            if(j&(1<<u)) hash_mask[i][j][k] ^= random_number[(i*8+u)*2+k];
        }
    }
}

ull make_hash(ull me, ull op){
    ull ret = 0;
    rep(i,64){
        if(me&(1ULL<<i)) ret ^= random_number[i*2];
        else if(op&(1ULL<<i)) ret ^= random_number[i*2+1];
    }
    return ret;
}

