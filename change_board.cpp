#include "change_board.h"
#include "hash.h"

bool unhash_change_board(ull& black, ull& white, bool now, int h, int w){
#ifdef DEBUG
    unhash_change_board_counter++;
#endif
    bool ret = false;
    int id = (h<<3)+w;
    if(now){
        black |= (1ULL<<id);
        rep(i,8){
            int hh = h+dh[i], ww = w+dw[i];
            if(hh >= 8 || hh < 0 || ww >= 8 || ww < 0) continue;
            if(!(white&(1ULL<<((hh<<3)+ww)))) continue;
            for(int j = 1;; j++){
                hh += dh[i]; ww += dw[i];
                if(hh >= 8 || hh < 0 || ww >= 8 || ww < 0) break;
                if(white&(1ULL<<((hh<<3)+ww))) continue;
                if(black&(1ULL<<((hh<<3)+ww))){
                    ret = true;
                    for(int u = 0; u < j; u++){
                        hh -= dh[i]; ww -= dw[i];
                        int new_id = (hh<<3)+ww;
                        
                        white &= ~(1ULL<<new_id);
                        
                        black |= (1ULL<<new_id);
                    }
                }
                break;
            }
        }
    } else{
        white |= (1ULL<<id);
        rep(i,8){
            int hh = h+dh[i], ww = w+dw[i];
            if(hh >= 8 || hh < 0 || ww >= 8 || ww < 0) continue;
            if(!(black&(1ULL<<((hh<<3)+ww)))) continue;
            for(int j = 1;; j++){
                hh += dh[i]; ww += dw[i];
                if(hh >= 8 || hh < 0 || ww >= 8 || ww < 0) break;
                if(black&(1ULL<<((hh<<3)+ww))) continue;
                if(white&(1ULL<<((hh<<3)+ww))){
                    ret = true;
                    for(int u = 0; u < j; u++){
                        hh -= dh[i]; ww -= dw[i];
                        int new_id = (hh<<3)+ww;
                        
                        black &= ~(1ULL<<new_id);
                        
                        white |= (1ULL<<new_id);
                    }
                }
                break;
            }
        }
    }
    return ret;
}

bool hash_change_board(ull& black, ull& white, bool now, int h, int w, ll& hasher){
#ifdef DEBUG
    hash_change_board_counter++;
#endif
    hasher ^= random_number[64*2];
    int id = (h<<3)+w;
    bool ret = false;
    if(now){
        black |= (1ULL<<id);
        hasher ^= random_number[id*2];
        rep(i,8){
            int hh = h+dh[i], ww = w+dw[i];
            if(hh >= 8 || hh < 0 || ww >= 8 || ww < 0) continue;
            if(!(white&(1ULL<<((hh<<3)+ww)))) continue;
            for(int j = 1;; j++){
                hh += dh[i]; ww += dw[i];
                if(hh >= 8 || hh < 0 || ww >= 8 || ww < 0) break;
                if(white&(1ULL<<((hh<<3)+ww))) continue;
                if(black&(1ULL<<((hh<<3)+ww))){
                    ret = true;
                    for(int u = 0; u < j; u++){
                        hh -= dh[i]; ww -= dw[i];
                        int new_id = (hh<<3)+ww;
                        
                        white &= ~(1ULL<<new_id);
                        hasher ^= random_number[new_id*2+1];
                        
                        black |= (1ULL<<new_id);
                        hasher ^= random_number[new_id*2];
                    }
                }
                break;
            }
        }
    } else{
        white |= (1ULL<<id);
        hasher ^= random_number[id*2+1];
        rep(i,8){
            int hh = h+dh[i], ww = w+dw[i];
            if(hh >= 8 || hh < 0 || ww >= 8 || ww < 0) continue;
            if(!(black&(1ULL<<((hh<<3)+ww)))) continue;
            for(int j = 1;; j++){
                hh += dh[i]; ww += dw[i];
                if(hh >= 8 || hh < 0 || ww >= 8 || ww < 0) break;
                if(black&(1ULL<<((hh<<3)+ww))) continue;
                if(white&(1ULL<<((hh<<3)+ww))){
                    ret = true;
                    for(int u = 0; u < j; u++){
                        hh -= dh[i]; ww -= dw[i];
                        int new_id = (hh<<3)+ww;
                        
                        black &= ~(1ULL<<new_id);
                        hasher ^= random_number[new_id*2];
                        
                        white |= (1ULL<<new_id);
                        hasher ^= random_number[new_id*2+1];
                    }
                }
                break;
            }
        }
    }
    return ret;
}
