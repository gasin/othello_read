#include "change_board.h"
#include "hash.h"

ull flip(int pos, ull me, ull op){
    ull flipped, outflank, mask;
    ull ret = 0ULL;
    
    mask = 0x0080808080808080ULL >> (63 - pos);
    outflank = (0x8000000000000000ULL >> __builtin_clzll(~op & mask)) & me; 
    flipped  = (-outflank * 2) & mask; 
    mask = 0x0101010101010100ULL << pos;
    outflank = mask & ((op | ~mask) + 1) & me;
    flipped |= (outflank - (outflank != 0)) & mask;
    ret |= flipped;
    
    op &= 0x7e7e7e7e7e7e7e7eULL;
    mask = 0x7f00000000000000ULL >> (63 - pos);
    outflank = (0x8000000000000000ULL >> __builtin_clzll(~op & mask)) & me;
    flipped  = (-outflank * 2) & mask;
    mask = 0x00000000000000feULL << pos;
    outflank = mask & ((op | ~mask) + 1) & me;
    flipped |= (outflank - (outflank != 0)) & mask;
    ret |= flipped;
    
    mask = 0x0102040810204000ULL >> (63 - pos);
    outflank = (0x8000000000000000ULL >> __builtin_clzll(~op & mask)) & me;
    flipped  = (-outflank * 2) & mask;
    mask = 0x0002040810204080ULL << pos;
    outflank = mask & ((op | ~mask) + 1) & me;
    flipped |= (outflank - (outflank != 0)) & mask;
    ret |= flipped;
    
    mask = 0x0040201008040201ULL >> (63 - pos);
    outflank = (0x8000000000000000ULL >> __builtin_clzll(~op & mask)) & me;
    flipped  = (-outflank * 2) & mask;
    mask = 0x8040201008040200ULL << pos;
    outflank = mask & ((op | ~mask) + 1) & me;
    flipped |= (outflank - (outflank != 0)) & mask;
    ret |= flipped;
    
    return ret;
}

bool unhash_change_board(ull& me, ull& op, int z){
#ifdef DEBUG
    unhash_change_board_counter++;
#endif
    ull f = flip(z,me,op);
    if(!f) return false;
    
    me |= (1ULL<<z);
    op &= ~f;
    me |= f;
        
    return true;
}

