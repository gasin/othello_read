#include "search.h"
#include "hash.h"
#include "change_board.h"

int black_final_search(ull& black, ull& white, int h, int w){
#ifdef DEBUG
    final_search_counter++;
#endif
    int ret = __builtin_popcountll(black)-__builtin_popcountll(white)+1;
    int tmp = ret;
    
    int z = h*8+w, zz, k;
    
    zz = z; k = 7-h;
    for(int j = 0; j < k; j++){
        zz += 8;
        if(white&(1ULL<<zz)) continue;
        if(black&(1ULL<<zz)) ret += j*2;
        break;
    }
    zz = z; k = min(7-w,7-h);
    for(int j = 0; j < k; j++){
        zz += 9;
        if(white&(1ULL<<zz)) continue;
        if(black&(1ULL<<zz)) ret += j*2;
        break;
    }
    zz = z; k = 7-w;
    for(int j = 0; j < k; j++){
        zz++;
        if(white&(1ULL<<zz)) continue;
        if(black&(1ULL<<zz)) ret += j*2;
        break;
    }
    zz = z; k = min(h,7-w);
    for(int j = 0; j < k; j++){
        zz -= 7;
        if(white&(1ULL<<zz)) continue;
        if(black&(1ULL<<zz)) ret += j*2;
        break;
    }
    zz = z;
    for(int j = 0; j < h; j++){
        zz -= 8;
        if(white&(1ULL<<zz)) continue;
        if(black&(1ULL<<zz)) ret += j*2;
        break;
    }
    zz = z; k = min(h,w);
    for(int j = 0; j < k; j++){
        zz -= 9;
        if(white&(1ULL<<zz)) continue;
        if(black&(1ULL<<zz)) ret += j*2;
        break;
    }
    zz = z;
    for(int j = 0; j < w; j++){
        zz--;
        if(white&(1ULL<<zz)) continue;
        if(black&(1ULL<<zz)) ret += j*2;
        break;
    }
    zz = z; k = min(7-h,w);
    for(int j = 0; j < k; j++){
        zz += 7;
        if(white&(1ULL<<zz)) continue;
        if(black&(1ULL<<zz)) ret += j*2;
        break;
    }

    if(ret == tmp) return INF;
    return ret;
}

int white_final_search(ull& black, ull& white, int h, int w){
#ifdef DEBUG
    final_search_counter++;
#endif
    int ret = __builtin_popcountll(black)-__builtin_popcountll(white)-1;
    int tmp = ret;
    
    int z = h*8+w, zz, k;
    
    zz = z; k = 7-h;
    for(int j = 0; j < k; j++){
        zz += 8;
        if(black&(1ULL<<zz)) continue;
        if(white&(1ULL<<zz)) ret -= j*2;
        break;
    }
    zz = z; k = min(7-w,7-h);
    for(int j = 0; j < k; j++){
        zz += 9;
        if(black&(1ULL<<zz)) continue;
        if(white&(1ULL<<zz)) ret -= j*2;
        break;
    }
    zz = z; k = 7-w;
    for(int j = 0; j < k; j++){
        zz++;
        if(black&(1ULL<<zz)) continue;
        if(white&(1ULL<<zz)) ret -= j*2;
        break;
    }
    zz = z; k = min(h,7-w);
    for(int j = 0; j < k; j++){
        zz -= 7;
        if(black&(1ULL<<zz)) continue;
        if(white&(1ULL<<zz)) ret -= j*2;
        break;
    }
    zz = z;
    for(int j = 0; j < h; j++){
        zz -= 8;
        if(black&(1ULL<<zz)) continue;
        if(white&(1ULL<<zz)) ret -= j*2;
        break;
    }
    zz = z; k = min(h,w);
    for(int j = 0; j < k; j++){
        zz -= 9;
        if(black&(1ULL<<zz)) continue;
        if(white&(1ULL<<zz)) ret -= j*2;
        break;
    }
    zz = z;
    for(int j = 0; j < w; j++){
        zz--;
        if(black&(1ULL<<zz)) continue;
        if(white&(1ULL<<zz)) ret -= j*2;
        break;
    }
    zz = z; k = min(7-h,w);
    for(int j = 0; j < k; j++){
        zz += 7;
        if(black&(1ULL<<zz)) continue;
        if(white&(1ULL<<zz)) ret -= j*2;
        break;
    }

    if(ret == tmp) return INF;
    return ret;
}

int unhash_search(ull black, ull white, int empty[EMPTY_AREA+1], bool now, bool suc){
    int bit_count = __builtin_popcountll(black|white);
    if(bit_count == 64) return __builtin_popcountll(black)-__builtin_popcountll(white);
    if(bit_count == 63){
        int f;
        if(now) f = black_final_search(black,white,empty[0]/8,empty[0]%8);
        else f = white_final_search(black,white,empty[0]/8,empty[0]%8);
        if(f == INF){
            if(suc){
                return __builtin_popcount(black)-__builtin_popcount(white);
            }
            return unhash_search(black,white,empty,now^1,true);
        }
        return f;
    }
#ifdef DEBUG
    unhash_search_counter++;
#endif
    
    bool draw = false;
    bool can_put = false;
    int next_empty[EMPTY_AREA+1];
    for(int u = 1; u < EMPTY_AREA+1; u++){
        if(empty[u] == -1){
            next_empty[u-1] = -1;
            break;
        }
        next_empty[u-1] = empty[u];
    }
    rep(u,EMPTY_AREA+1){
        if(empty[u] < 0) break;
        if(u) next_empty[u-1] = empty[u-1];
        int i = empty[u]/8, j = empty[u]%8;
        ull newblack = black, newwhite = white;
        if(!unhash_change_board(newblack,newwhite,now,i,j)){
            continue;
        }
        can_put = true;
        int rec = unhash_search(newblack,newwhite,next_empty,now^1,false);
        if(rec == 0) draw = true;
        else if(rec > 0 && now == true){
            return 1;
        }
        else if(rec < 0 && now == false){
            return -1;
        }
    }
    if(can_put){
        if(draw) return 0;
        if(now) return -1;
        else return 1;
    }
    if(suc){
        return __builtin_popcountll(black)-__builtin_popcountll(white);
    }
    return unhash_search(black,white,empty,now^1,true);
}

int hash_search(ull black, ull white, int empty[EMPTY_AREA+1], bool now, bool suc, ull hasher, int depth){
    int bit_count = __builtin_popcountll(black|white);
    if(bit_count == 64) return __builtin_popcountll(black)-__builtin_popcountll(white);
    
    if(bit_count == 63){
        int f;
        if(now) f = black_final_search(black,white,empty[0]/8,empty[0]%8);
        else f = white_final_search(black,white,empty[0]/8,empty[0]%8);
        if(f == INF){
            if(suc){
                //return hash_table[hash_index][hasher] = __builtin_popcount(black)-__builtin_popcountll(white);
                return __builtin_popcount(black)-__builtin_popcountll(white);
            }
            //return hash_table[hash_index][hasher] = hash_search(black,white,empty,now^1,true,hasher^random_number[64*2],depth,hash_index);
            return hash_search(black,white,empty,now^1,true,hasher^random_number[64*2],depth);
        }
        return f;
    }
    if(hash_table.count(hasher)){
        return hash_table[hasher];
    }
#ifdef DEBUG
    hash_search_counter++;
#endif
    bool draw = false;
    bool can_put = false;
    int next_empty[EMPTY_AREA+1];
    for(int u = 1; u < EMPTY_AREA+1; u++){
        if(empty[u] == -1){
            next_empty[u-1] = -1;
            break;
        }
        next_empty[u-1] = empty[u];
    }
    rep(u,EMPTY_AREA+1){
        if(empty[u] < 0) break;
        if(u) next_empty[u-1] = empty[u-1];
        int i = empty[u]/8, j = empty[u]%8;
        ull new_hasher = hasher;
        ull newblack = black, newwhite = white;
        if(!hash_change_board(newblack,newwhite,now,i,j,new_hasher)){
            continue;
        }
        can_put = true;
        int rec;
        if(depth >= HASH_DEPTH){
            rec = unhash_search(newblack,newwhite,next_empty,now^1,false);
        } else{
            rec = hash_search(newblack,newwhite,next_empty,now^1,false,new_hasher,depth+1);
        }
        if(rec == 0) draw = true;
        else if(rec > 0 && now == true){
            return hash_table[hasher] = 1;
        }
        else if(rec < 0 && now == false){
            return hash_table[hasher] = -1;
        }
    }
    if(can_put){
        if(draw) return hash_table[hasher] = 0;
        if(now) return hash_table[hasher] = -1;
        else return hash_table[hasher] = 1;
    }
    if(suc){
        return hash_table[hasher] = __builtin_popcountll(black)-__builtin_popcountll(white);
    }
    return hash_table[hasher] = hash_search(black,white,empty,now^1,true,hasher^random_number[64*2],depth);
}

int firstsearch(ull black, ull white, bool now){
    int ret = INF;
    int empty[EMPTY_AREA+1], next_empty[EMPTY_AREA+1];
    int counter = 0;
    rep(i,8) rep(j,8) if(!((black|white)&(1ULL<<(i*8+j)))){
        if(counter) next_empty[counter-1] = i*8+j;
        empty[counter++] = i*8+j;
    }
    empty[counter] = -1;
    next_empty[counter-1] = -1;
    ull hasher = make_hash(black, white, now);
    rep(u,EMPTY_AREA+1){
        if(empty[u] < 0) break;
        if(u) next_empty[u-1] = empty[u-1];
        int i = empty[u]/8, j = empty[u]%8;
        ull new_hasher = hasher;
        ull newblack = black, newwhite = white;
        if(!hash_change_board(newblack,newwhite,now,i,j,new_hasher)){
        //if(!unhash_change_board(newblack,newwhite,now,i,j)){
            continue;
        }
        cout << i << " " << j << " " << hash_table.size() << endl;
        int rec = hash_search(newblack,newwhite,next_empty,now^1,false,new_hasher,1);
        //int rec = unhash_search(newblack,newwhite,next_empty,now^1,false);
        if(rec == 0) ret = -(empty[u]+1);
        else if(rec > 0 && now == true) return (empty[u]+1);
        else if(rec < 0 && now == false) return (empty[u]+1);
    }
    return ret;
}
