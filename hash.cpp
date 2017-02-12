#include "hash.h"

unordered_map<int, vector<HASH_DATA>> hash_table;
int random_number[RANDOM_NUMBER];

void init_random(){
	mt19937 mt(114514);
    for(int i = 0; i < RANDOM_NUMBER; i++){
        random_number[i] = mt();
        if(random_number[i] < 0) random_number[i] *= -1;
    }
}

P make_board(bitset<64> black, bitset<64> white, bool now){
    ll x = now, y = 0;
    rep(i,32){
        x *= 3;
        y *= 3;
        if(black[i]) x++;
        else if(white[i]) x += 2;
        if(black[i+32]) y++;
        else if(white[i+32]) y += 2;
    }
    return P(x,y);
}

int make_hash(bitset<64> black, bitset<64> white, bool now){
    int ret = 0;
    int pointer = 0;
    rep(i,64){
        if(black[i]) ret ^= random_number[pointer];
        else if(white[i]) ret ^= random_number[pointer+1];
        else ret ^= random_number[pointer+2];
        pointer += 3;
    }
    if(now) ret ^= random_number[pointer];
    else ret ^= random_number[pointer+1];
    return ret;
}

