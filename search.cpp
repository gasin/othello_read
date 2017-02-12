#include "search.h"
#include "hash.h"
#include "change_board.h"

int black_final_search(bitset<64>& black, bitset<64>& white, int h, int w){
    int ret = black.count()-white.count()+1;
    int tmp = ret;
    rep(i,8){
        int hh = h+dh[i], ww = w+dw[i];
        if(hh >= 8 || hh < 0 || ww >= 8 || ww < 0) continue;
        if(!white[(hh<<3)+ww]) continue;
        for(int j = 1;; j++){
            hh += dh[i]; ww += dw[i];
            if(hh >= 8 || hh < 0 || ww >= 8 || ww < 0) break;
            if(white[(hh<<3)+ww]) continue;
            if(black[(hh<<3)+ww]){
                ret += j*2;
            }
            break;
        }
    }
    if(ret == tmp) return INF;
    return ret;
}

int white_final_search(bitset<64>& black, bitset<64>& white, int h, int w){
    int ret = black.count()-white.count()-1;
    int tmp = ret;
    rep(i,8){
        int hh = h+dh[i], ww = w+dw[i];
        if(hh >= 8 || hh < 0 || ww >= 8 || ww < 0) continue;
        if(!black[(hh<<3)+ww]) continue;
        for(int j = 1;; j++){
            hh += dh[i]; ww += dw[i];
            if(hh >= 8 || hh < 0 || ww >= 8 || ww < 0) break;
            if(black[(hh<<3)+ww]) continue;
            if(white[(hh<<3)+ww]){
                ret -= j*2;
            }
            break;
        }
    }
    if(ret == tmp) return INF;
    return ret;
}

int unhash_search(bitset<64> black, bitset<64> white, int empty[EMPTY_AREA+1], bool now, bool suc){
    int bit_count = (black|white).count();
    if(bit_count == 64) return black.count()-white.count();
    if(bit_count == 63){
        int f;
        if(now) f = black_final_search(black,white,empty[0]/8,empty[0]%8);
        else f = white_final_search(black,white,empty[0]/8,empty[0]%8);
        if(f == INF){
            if(suc){
                return black.count()-white.count();
            }
            return unhash_search(black,white,empty,now^1,true);
        }
        return f;
    }
    
    bool draw = false;
    bool can_put = false;
    bitset<64> newblack(0), newwhite(0);
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
        newblack = black; newwhite = white;
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
        return black.count()-white.count();
    }
    return unhash_search(black,white,empty,now^1,true);
}

int hash_search(bitset<64> black, bitset<64> white, int empty[EMPTY_AREA+1], bool now, bool suc, ll hasher, int depth){
    int bit_count = (black|white).count();
    if(bit_count == 64) return black.count()-white.count();
    if(bit_count == 63){
        int f;
        if(now) f = black_final_search(black,white,empty[0]/8,empty[0]%8);
        else f = white_final_search(black,white,empty[0]/8,empty[0]%8);
        if(f == INF){
            if(suc){
                return black.count()-white.count();
            }
            return hash_search(black,white,empty,now^1,true,hasher,depth);
        }
        return f;
    }
    
    if(hash_table.count(hasher)){
        return hash_table[hasher];
    }
    bool draw = false;
    bool can_put = false;
    bitset<64> newblack(0), newwhite(0);
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
        newblack = black; newwhite = white;
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
        return hash_table[hasher] = black.count()-white.count();
    }
    hasher ^= random_number[64*2];
    return hash_table[hasher] = hash_search(black,white,empty,now^1,true,hasher,depth);
}

int firstsearch(bitset<64> black, bitset<64> white, bool now){
    int ret = INF;
    int empty[EMPTY_AREA+1], next_empty[EMPTY_AREA+1];
    int counter = 0;
    rep(i,8) rep(j,8) if(!(black|white)[i*8+j]){
        if(counter) next_empty[counter-1] = i*8+j;
        empty[counter++] = i*8+j;
    }
    empty[counter] = -1;
    next_empty[counter-1] = -1;
    ll hasher = make_hash(black, white, now);
    bitset<64> newblack(0), newwhite(0);
    rep(u,EMPTY_AREA+1){
        if(empty[u] < 0) break;
        if(u) next_empty[u-1] = empty[u-1];
        int i = empty[u]/8, j = empty[u]%8;
        ll new_hasher = hasher;
        newblack = black; newwhite = white;
        if(!hash_change_board(newblack,newwhite,now,i,j,new_hasher)){
        //if(!unhash_change_board(newblack,newwhite,now,i,j)){
            continue;
        }
        int rec = hash_search(newblack,newwhite,next_empty,now^1,false,new_hasher,0);
        //int rec = unhash_search(newblack,newwhite,next_empty,now^1,false);
        if(rec == 0) ret = -(empty[u]+1);
        else if(rec > 0 && now == true) return (empty[u]+1);
        else if(rec < 0 && now == false) return (empty[u]+1);
    }
    return ret;
}
