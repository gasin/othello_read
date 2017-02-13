#include "search.h"
#include "hash.h"
#include "change_board.h"

int black_final_search(ull& black, ull& white, int h, int w){
#ifdef DEBUG
    final_search_counter++;
#endif
    int ret = __builtin_popcountll(black)-__builtin_popcountll(white)+1;
    int tmp = ret;
    rep(i,8){
        int hh = h+dh[i], ww = w+dw[i];
        if(hh >= 8 || hh < 0 || ww >= 8 || ww < 0) continue;
        if(!(white&(1ULL<<((hh<<3)+ww)))) continue;
        for(int j = 1;; j++){
            hh += dh[i]; ww += dw[i];
            if(hh >= 8 || hh < 0 || ww >= 8 || ww < 0) break;
            if(white&(1ULL<<((hh<<3)+ww))) continue;
            if(black&(1ULL<<((hh<<3)+ww))){
                ret += j*2;
            }
            break;
        }
    }
    /*
    int hh = h+1, ww = w;
    if(hh <= 6 && white[(hh<<3)+ww]){
        for(int j = 1;; j++){
            hh++;
            if(hh >= 8) break;
            if(white[(hh<<3)+ww]) continue;
            if(black[(hh<<3)+ww]) ret += j*2;
            break;
        }
    }
    hh = h+1; ww = w+1;
    if(hh <= 6 && ww <= 6 && white[(hh<<3)+ww]){
        for(int j = 1;; j++){
            hh++; ww++;
            if(hh >= 8 || ww >= 8) break;
            if(white[(hh<<3)+ww]) continue;
            if(black[(hh<<3)+ww]) ret += j*2;
            break;
        }
    }
    hh = h; ww = w+1;
    if(ww <= 6 && white[(hh<<3)+ww]){
        for(int j = 1;; j++){
            ww++;
            if(ww >= 8) break;
            if(white[(hh<<3)+ww]) continue;
            if(black[(hh<<3)+ww]) ret += j*2; 
            break;
        }
    }
    hh = h-1; ww = w+1;
    if(hh >= 1 && ww <= 6 && white[(hh<<3)+ww]){
        for(int j = 1;; j++){
            hh--; ww++;
            if(hh < 0 || ww >= 8) break;
            if(white[(hh<<3)+ww]) continue;
            if(black[(hh<<3)+ww]) ret += j*2;
            break;
        }
    }
    hh = h-1; ww = w;
    if(hh >= 1 && white[(hh<<3)+ww]){
        for(int j = 1;; j++){
            hh--;
            if(hh < 0) break;
            if(white[(hh<<3)+ww]) continue;
            if(black[(hh<<3)+ww]) ret += j*2;
            break;
        }
    }
    hh = h-1; ww = w-1;
    if(hh >= 1 && ww >= 1 && white[(hh<<3)+ww]){
        for(int j = 1;; j++){
            hh--; ww--;
            if(hh < 0 || ww < 0) break;
            if(white[(hh<<3)+ww]) continue;
            if(black[(hh<<3)+ww]) ret += j*2;
            break;
        }
    }
    hh = h; ww = w-1;
    if(ww >= 1 && white[(hh<<3)+ww]){
        for(int j = 1;; j++){
            ww--;
            if(ww < 0) break;
            if(white[(hh<<3)+ww]) continue;
            if(black[(hh<<3)+ww]) ret += j*2;
            break;
        }
    }
    hh = h+1; ww = w-1;
    if(hh <= 6 && ww >= 1 && white[(hh<<3)+ww]){
        for(int j = 1;; j++){
            hh++; ww--;
            if(hh >= 8 || ww < 0) break;
            if(white[(hh<<3)+ww]) continue;
            if(black[(hh<<3)+ww]) ret += j*2;
            break;
        }
    }
    */

    if(ret == tmp) return INF;
    return ret;
}

int white_final_search(ull& black, ull& white, int h, int w){
#ifdef DEBUG
    final_search_counter++;
#endif
    int ret = __builtin_popcountll(black)-__builtin_popcountll(white)-1;
    int tmp = ret;
    rep(i,8){
        int hh = h+dh[i], ww = w+dw[i];
        if(hh >= 8 || hh < 0 || ww >= 8 || ww < 0) continue;
        if(!(black&(1ULL<<((hh<<3)+ww)))) continue;
        for(int j = 1;; j++){
            hh += dh[i]; ww += dw[i];
            if(hh >= 8 || hh < 0 || ww >= 8 || ww < 0) break;
            if(black&(1ULL<<((hh<<3)+ww))) continue;
            if(white&(1ULL<<((hh<<3)+ww))){
                ret -= j*2;
            }
            break;
        }
    }
    /*
    int hh = h+1, ww = w;
    if(hh <= 6 && black[(hh<<3)+ww]){
        for(int j = 1;; j++){
            hh++;
            if(hh >= 8) break;
            if(black[(hh<<3)+ww]) continue;
            if(white[(hh<<3)+ww]) ret -= j*2;
            break;
        }
    }
    hh = h+1; ww = w+1;
    if(hh <= 6 && ww <= 6 && black[(hh<<3)+ww]){
        for(int j = 1;; j++){
            hh++; ww++;
            if(hh >= 8 || ww >= 8) break;
            if(black[(hh<<3)+ww]) continue;
            if(white[(hh<<3)+ww]) ret -= j*2;
            break;
        }
    }
    hh = h; ww = w+1;
    if(ww <= 6 && black[(hh<<3)+ww]){
        for(int j = 1;; j++){
            ww++;
            if(ww >= 8) break;
            if(black[(hh<<3)+ww]) continue;
            if(white[(hh<<3)+ww]) ret -= j*2; 
            break;
        }
    }
    hh = h-1; ww = w+1;
    if(hh >= 1 && ww <= 6 && black[(hh<<3)+ww]){
        for(int j = 1;; j++){
            hh--; ww++;
            if(hh < 0 || ww >= 8) break;
            if(black[(hh<<3)+ww]) continue;
            if(white[(hh<<3)+ww]) ret -= j*2;
            break;
        }
    }
    hh = h-1; ww = w;
    if(hh >= 1 && black[(hh<<3)+ww]){
        for(int j = 1;; j++){
            hh--;
            if(hh < 0) break;
            if(black[(hh<<3)+ww]) continue;
            if(white[(hh<<3)+ww]) ret -= j*2;
            break;
        }
    }
    hh = h-1; ww = w-1;
    if(hh >= 1 && ww >= 1 && black[(hh<<3)+ww]){
        for(int j = 1;; j++){
            hh--; ww--;
            if(hh < 0 || ww < 0) break;
            if(black[(hh<<3)+ww]) continue;
            if(white[(hh<<3)+ww]) ret -= j*2;
            break;
        }
    }
    hh = h; ww = w-1;
    if(ww >= 1 && black[(hh<<3)+ww]){
        for(int j = 1;; j++){
            ww--;
            if(ww < 0) break;
            if(black[(hh<<3)+ww]) continue;
            if(white[(hh<<3)+ww]) ret -= j*2;
            break;
        }
    }
    hh = h+1; ww = w-1;
    if(hh <= 6 && ww >= 1 && black[(hh<<3)+ww]){
        for(int j = 1;; j++){
            hh++; ww--;
            if(hh >= 8 || ww < 0) break;
            if(black[(hh<<3)+ww]) continue;
            if(white[(hh<<3)+ww]) ret -= j*2;
            break;
        }
    }
    */
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

int hash_search(ull black, ull white, int empty[EMPTY_AREA+1], bool now, bool suc, ll hasher, int depth){
    int bit_count = __builtin_popcountll(black|white);
    if(bit_count == 64) return __builtin_popcountll(black)-__builtin_popcountll(white);
    if(bit_count == 63){
        int f;
        if(now) f = black_final_search(black,white,empty[0]/8,empty[0]%8);
        else f = white_final_search(black,white,empty[0]/8,empty[0]%8);
        if(f == INF){
            if(suc){
                return __builtin_popcount(black)-__builtin_popcountll(white);
            }
            return hash_search(black,white,empty,now^1,true,hasher,depth);
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
        ll new_hasher = hasher;
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
    ll hasher = make_hash(black, white, now);
    rep(u,EMPTY_AREA+1){
        if(empty[u] < 0) break;
        if(u) next_empty[u-1] = empty[u-1];
        int i = empty[u]/8, j = empty[u]%8;
        ll new_hasher = hasher;
        ull newblack = black, newwhite = white;
        if(!hash_change_board(newblack,newwhite,now,i,j,new_hasher)){
        //if(!unhash_change_board(newblack,newwhite,now,i,j)){
            continue;
        }
        cout << i << " " << j << " " << hash_table.size() << endl;
        int rec = hash_search(newblack,newwhite,next_empty,now^1,false,new_hasher,0);
        //int rec = unhash_search(newblack,newwhite,next_empty,now^1,false);
        if(rec == 0) ret = -(empty[u]+1);
        else if(rec > 0 && now == true) return (empty[u]+1);
        else if(rec < 0 && now == false) return (empty[u]+1);
    }
    return ret;
}
