#include "change_board.h"
#include "hash.h"

bool unhash_change_board(bitset<64>& black, bitset<64>& white, bool now, int h, int w){
    int id = (h<<3)+w;
    if(now){
        black.set(id);
    } else{
        white.set(id);
    }
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
                        int new_id = (hh<<3)+ww;
                        
                        white.reset(new_id);
                        
                        black.set(new_id);
                    }
                }
                break;
            } else{
                if(black[(hh<<3)+ww]) continue;
                if(white[(hh<<3)+ww]){
                    ret = true;
                    for(int u = 0; u < j; u++){
                        hh -= dh[i]; ww -= dw[i];
                        int new_id = (hh<<3)+ww;
                        
                        black.reset(new_id);
                        
                        white.set(new_id);
                    }
                }
                break;
            }
        }
    }
    return ret;
}

bool hash_change_board(bitset<64>& black, bitset<64>& white, bool now, int h, int w, ll& hasher){
    hasher ^= random_number[64*2];
    
    int id = (h<<3)+w;
    if(now){
        black.set(id);
        hasher ^= random_number[id*2];
    } else{
        white.set(id);
        hasher ^= random_number[id*2+1];
    }
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
                        int new_id = (hh<<3)+ww;
                        
                        white.reset(new_id);
                        hasher ^= random_number[new_id*2+1];
                        
                        black.set(new_id);
                        hasher ^= random_number[new_id*2];
                    }
                }
                break;
            } else{
                if(black[(hh<<3)+ww]) continue;
                if(white[(hh<<3)+ww]){
                    ret = true;
                    for(int u = 0; u < j; u++){
                        hh -= dh[i]; ww -= dw[i];
                        int new_id = (hh<<3)+ww;
                        
                        black.reset(new_id);
                        hasher ^= random_number[new_id*2];
                        
                        white.set(new_id);
                        hasher ^= random_number[new_id*2+1];
                    }
                }
                break;
            }
        }
    }
    return ret;
}




























