#include "search.h"
#include "hash.h"

bool change_board(bitset<64>& black, bitset<64>& white, bool now, int h, int w){
    if(now) black.set((h<<3)+w);
    else white.set((h<<3)+w);
    bool ret = false;
    rep(i,8){
        int hh = h+dh[i], ww = w+dw[i];
        if(hh >= 8 || hh < 0 || ww >= 8 || ww < 0) continue;
        if(now && !white[(hh<<3)+ww]) continue;
        if(!now && !black[(hh<<3)+ww]) continue;
        for(int j = 1;; j++){
            hh += dh[i]; ww += dw[i];
            if(hh >= 8 || hh < 0 || ww >= 8 || ww < 0) break;
            if(now){
                if(white[(hh<<3)+ww]) continue;
                if(black[(hh<<3)+ww]){
                    ret = true;
                    for(int u = 0; u < j; u++){
                        hh -= dh[i]; ww -= dw[i];
                        white.reset((hh<<3)+ww);
                        black.set((hh<<3)+ww);
                    }
                }
                break;
            } else{
                if(black[(hh<<3)+ww]) continue;
                if(white[(hh<<3)+ww]){
                    ret = true;
                    for(int u = 0; u < j; u++){
                        hh -= dh[i]; ww -= dw[i];
                        black.reset((hh<<3)+ww);
                        white.set((hh<<3)+ww);
                    }
                }
                break;
            }
        }
    }
    return ret;
}

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

int search(bitset<64> black, bitset<64> white, int empty[EMPTY_AREA+1], bool now, bool suc){
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
            return search(black,white,empty,now^1,true);
        }
        return f;
    }
    
    P board = make_board(black,white,now);
    int hasher = make_hash(black,white,now);
    if(hash_table.count(hasher)){
        rep(i,hash_table[hasher].size()){
            if(hash_table[hasher][i].board == board){
                return hash_table[hasher][i].val;
            }
        }
    }
    hash_table[hasher].push_back((HASH_DATA){board,0});
    int hash_pos = hash_table[hasher].size()-1;
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
        if(!change_board(newblack,newwhite,now,i,j)){
            continue;
        }
        can_put = true;
        int rec = search(newblack,newwhite,next_empty,now^1,false);
        if(rec == 0) draw = true;
        else if(rec > 0 && now == true){
            return hash_table[hasher][hash_pos].val = 1;
        }
        else if(rec < 0 && now == false){
            return hash_table[hasher][hash_pos].val = -1;
        }
    }
    if(can_put){
        if(draw) return hash_table[hasher][hash_pos].val = 0;
        if(now) return hash_table[hasher][hash_pos].val = -1;
        else return hash_table[hasher][hash_pos].val = 1;
    }
    if(suc){
        return hash_table[hasher][hash_pos].val = black.count()-white.count();
    }
    return hash_table[hasher][hash_pos].val = search(black,white,empty,now^1,true);
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
    bitset<64> newblack(0), newwhite(0);
    rep(u,EMPTY_AREA+1){
        if(empty[u] < 0) break;
        if(u) next_empty[u-1] = empty[u-1];
        int i = empty[u]/8, j = empty[u]%8;
        newblack = black; newwhite = white;
        if(!change_board(newblack,newwhite,now,i,j)){
            continue;
        }
        int rec = search(newblack,newwhite,next_empty,now^1,false);
        if(rec == 0) ret = -(empty[u]+1);
        else if(rec > 0 && now == true) return (empty[u]+1);
        else if(rec < 0 && now == false) return (empty[u]+1);
    }
    return ret;
}
