#include "search.h"
#include "hash.h"
#include "change_board.h"

inline int flip_count(int pos, ull me, ull op){
    ull flipped, outflank, mask;
    int ret = 0;
    
    mask = 0x0080808080808080ULL >> (63 - pos);
    outflank = (0x8000000000000000ULL >> __builtin_clzll(~op & mask)) & me; 
    flipped  = (-outflank * 2) & mask; 
    mask = 0x0101010101010100ULL << pos;
    outflank = mask & ((op | ~mask) + 1) & me;
    flipped |= (outflank - (outflank != 0)) & mask;
    ret += __builtin_popcountll(flipped);
    
    op &= 0x7e7e7e7e7e7e7e7eULL;
    mask = 0x7f00000000000000ULL >> (63 - pos);
    outflank = (0x8000000000000000ULL >> __builtin_clzll(~op & mask)) & me;
    flipped  = (-outflank * 2) & mask;
    mask = 0x00000000000000feULL << pos;
    outflank = mask & ((op | ~mask) + 1) & me;
    flipped |= (outflank - (outflank != 0)) & mask;
    ret += __builtin_popcountll(flipped);
    
    mask = 0x0102040810204000ULL >> (63 - pos);
    outflank = (0x8000000000000000ULL >> __builtin_clzll(~op & mask)) & me;
    flipped  = (-outflank * 2) & mask;
    mask = 0x0002040810204080ULL << pos;
    outflank = mask & ((op | ~mask) + 1) & me;
    flipped |= (outflank - (outflank != 0)) & mask;
    ret += __builtin_popcountll(flipped);
    
    mask = 0x0040201008040201ULL >> (63 - pos);
    outflank = (0x8000000000000000ULL >> __builtin_clzll(~op & mask)) & me;
    flipped  = (-outflank * 2) & mask;
    mask = 0x8040201008040200ULL << pos;
    outflank = mask & ((op | ~mask) + 1) & me;
    flipped |= (outflank - (outflank != 0)) & mask;
    ret += __builtin_popcountll(flipped);
    
    return ret;
}


inline int final_search(ull me, ull op, int z){
#ifdef DEBUG
    final_search_counter++;
#endif
    int ret = __builtin_popcountll(me)-__builtin_popcountll(op)+1;
    
    int f = flip_count(z,me,op);
    
    return f==0?INF:ret+f*2;
}

int unhash_search(ull me, ull op, int empty[EMPTY_AREA+1], bool suc){
    int empty_count = __builtin_popcountll(me|op);
    //if(empty_count == 64) return __builtin_popcountll(me)-__builtin_popcountll(op);
    if(empty_count == 63){
        int f = final_search(me,op,empty[0]);
        if(f == INF){
            if(suc) return __builtin_popcount(me)-__builtin_popcount(op);
            return -1*unhash_search(op,me,empty,true);
        }
        return f;
    }
#ifdef DEBUG
    unhash_search_counter++;
#endif
    
    empty_count = 64-empty_count;
    int next_empty[EMPTY_AREA+1];
    bool draw = false, can_put = false;
    for(int u = 1; u < empty_count; u++) next_empty[u-1] = empty[u];
    for(int u = 0; u < empty_count; u++){
        if(u) next_empty[u-1] = empty[u-1];
        ull newme = me, newop = op;
        if(!unhash_change_board(newme,newop,empty[u])) continue;
        
        can_put = true;
        int rec = unhash_search(newop,newme,next_empty,false);
        if(rec < 0) return 1;
        if(rec == 0) draw = true;
    }
    if(can_put) return draw?0:-1;
    if(suc) return __builtin_popcountll(me)-__builtin_popcountll(op);
    return -1*unhash_search(op,me,empty,true);
}

int hash_search(ull me, ull op, int empty[EMPTY_AREA+1], bool suc, int depth){
    int empty_count = __builtin_popcountll(me|op);
    if(empty_count == 64) return __builtin_popcountll(me)-__builtin_popcountll(op);
    
    if(empty_count == 63){
        int f = final_search(me,op,empty[0]);
        if(f == INF){
            if(suc) return __builtin_popcount(me)-__builtin_popcountll(op);
            return -1*hash_search(op,me,empty,true,depth);
        }
        return f;
    }
    ull hasher = 0;
    rep(i,8){
        hasher ^= hash_mask[i][(me>>8*i)&255ULL][0];
        hasher ^= hash_mask[i][(op>>8*i)&255ULL][1];
    }
    if(hash_table.count(hasher)) return hash_table[hasher];
    
#ifdef DEBUG
    hash_search_counter++;
#endif
    empty_count = 64-empty_count;
    int next_empty[EMPTY_AREA+1];
    bool draw = false, can_put = false;
    for(int u = 1; u < empty_count; u++) next_empty[u-1] = empty[u];
    rep(u,empty_count){
        if(u) next_empty[u-1] = empty[u-1];
        ull newme = me, newop = op;
        if(!unhash_change_board(newme,newop,empty[u])) continue;
            
        can_put = true;
        int rec;
        if(depth >= HASH_DEPTH) rec = unhash_search(newop,newme,next_empty,false);
        else rec = hash_search(newop,newme,next_empty,false,depth+1);
        
        if(rec < 0) return hash_table[hasher] = 1;
        if(rec == 0) draw = true;
    }
    if(can_put) return hash_table[hasher] = draw?0:-1;
    if(suc) return hash_table[hasher] = __builtin_popcountll(me)-__builtin_popcountll(op);
    return hash_table[hasher] = -1*hash_search(op,me,empty,true,depth);
}

int firstsearch(ull me, ull op){
    int ret = INF;
    int empty[EMPTY_AREA+1], next_empty[EMPTY_AREA+1];
    int counter = 0;
    rep(i,8) rep(j,8) if(!((me|op)&(1ULL<<(i*8+j)))){
        if(counter) next_empty[counter-1] = i*8+j;
        empty[counter++] = i*8+j;
    }
    empty[counter] = -1;
    next_empty[counter-1] = -1;
    rep(u,counter){
        if(u) next_empty[u-1] = empty[u-1];
        ull newme = me, newop = op;
        if(!unhash_change_board(newme,newop,empty[u])){
            continue;
        }
        cout << empty[u]/8 << " " << empty[u]%8 << " " << hash_table.size() << endl;
        int rec = hash_search(newop,newme,next_empty,false,1);
        if(rec == 0) ret = -(empty[u]+1);
        else if(rec < 0) return (empty[u]+1);
    }
    return ret;
}
