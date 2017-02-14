#include "change_board.h"
#include "hash.h"
#include "preprocess.h"

bool unhash_change_board(ull& black, ull& white, bool now, int h, int w){
#ifdef DEBUG
    unhash_change_board_counter++;
#endif
    if(now){
        int z = h*8+w, zz, k;
        black |= (1ULL<<z);
        ull pre_black = black;
        
        zz = z+8; k = 7-h;
        if(k > 1 && (white&(1ULL<<zz))) for(int j = 1; j < k; j++){
            zz += 8;
            if(white&(1ULL<<zz)) continue;
            if(black&(1ULL<<zz)){
                white &= ~(bit_mask[z][0][j]);
                black |= bit_mask[z][0][j];
                /*
                for(int u = 0; u < j; u++){
                    zz -= 8;
                    white &= ~(1ULL<<zz);
                    black |= (1ULL<<zz);
                }
                */
            }
            break;
        }
        zz = z+9; k = min(7-w,7-h);
        if(k > 1 && (white&(1ULL<<zz))) for(int j = 1; j < k; j++){
            zz += 9;
            if(white&(1ULL<<zz)) continue;
            if(black&(1ULL<<zz)){
                white &= ~(bit_mask[z][1][j]);
                black |= bit_mask[z][1][j];
                /*
                for(int u = 0; u < j; u++){
                    zz -= 9;
                    white &= ~(1ULL<<zz);
                    black |= (1ULL<<zz);
                }
                */
            }
            break;
        }
        zz = z+1; k = 7-w;
        if(k > 1 && (white&(1ULL<<zz))) for(int j = 1; j < k; j++){
            zz++;
            if(white&(1ULL<<zz)) continue;
            if(black&(1ULL<<zz)){
                white &= ~(bit_mask[z][2][j]);
                black |= bit_mask[z][2][j];
                /*
                for(int u = 0; u < j; u++){
                    zz--;
                    white &= ~(1ULL<<zz);
                    black |= (1ULL<<zz);
                }
                */
            }
            break;
        }
        zz = z-7; k = min(h,7-w);
        if(k > 1 && (white&(1ULL<<zz))) for(int j = 1; j < k; j++){
            zz -= 7;
            if(white&(1ULL<<zz)) continue;
            if(black&(1ULL<<zz)){
                white &= ~(bit_mask[z][3][j]);
                black |= bit_mask[z][3][j];
                /*
                for(int u = 0; u < j; u++){
                    zz += 7;
                    white &= ~(1ULL<<zz);
                    black |= (1ULL<<zz);
                }
                */
            }
            break;
        }
        zz = z-8;
        if(h > 1 && (white&(1ULL<<zz))) for(int j = 1; j < h; j++){
            zz -= 8;
            if(white&(1ULL<<zz)) continue;
            if(black&(1ULL<<zz)){
                white &= ~(bit_mask[z][4][j]);
                black |= bit_mask[z][4][j];
                /*
                for(int u = 0; u < j; u++){
                    zz += 8;
                    white &= ~(1ULL<<zz);
                    black |= (1ULL<<zz);
                }
                */
            }
            break;
        }
        zz = z-9; k = min(h,w);
        if(k > 1 && (white&(1ULL<<zz))) for(int j = 1; j < k; j++){
            zz -= 9;
            if(white&(1ULL<<zz)) continue;
            if(black&(1ULL<<zz)){
                white &= ~(bit_mask[z][5][j]);
                black |= bit_mask[z][5][j];
                /*
                for(int u = 0; u < j; u++){
                    zz += 9;
                    white &= ~(1ULL<<zz);
                    black |= (1ULL<<zz);
                }
                */
            }
            break;
        }
        zz = z-1;
        if(w > 1 && (white&(1ULL<<zz))) for(int j = 1; j < w; j++){
            zz--;
            if(white&(1ULL<<zz)) continue;
            if(black&(1ULL<<zz)){
                white &= ~(bit_mask[z][6][j]);
                black |= bit_mask[z][6][j];
                /*
                for(int u = 0; u < j; u++){
                    zz++;
                    white &= ~(1ULL<<zz);
                    black |= (1ULL<<zz);
                }
                */
            }
            break;
        }
        zz = z+7; k = min(7-h,w);
        if(k > 1 && (white&(1ULL<<zz))) for(int j = 1; j < k; j++){
            zz += 7;
            if(white&(1ULL<<zz)) continue;
            if(black&(1ULL<<zz)){
                white &= ~(bit_mask[z][7][j]);
                black |= bit_mask[z][7][j];
                /*
                for(int u = 0; u < j; u++){
                    zz -= 7;
                    white &= ~(1ULL<<zz);
                    black |= (1ULL<<zz);
                }
                */
            }
            break;
        }
        return (pre_black != black);
        
    } else{
        int z = h*8+w, zz, k;
        white |= (1ULL<<z);
        ull pre_white = white;
        
        zz = z+8; k = 7-h;
        if(k > 1 && (black&(1ULL<<zz))) for(int j = 1; j < k; j++){
            zz += 8;
            if(black&(1ULL<<zz)) continue;
            if(white&(1ULL<<zz)){
                black &= ~(bit_mask[z][0][j]);
                white |= bit_mask[z][0][j];
                /*
                for(int u = 0; u < j; u++){
                    zz -= 8;
                    black &= ~(1ULL<<zz);
                    white |= (1ULL<<zz);
                }
                */
            }
            break;
        }
        zz = z+9; k = min(7-w,7-h);
        if(k > 1 && (black&(1ULL<<zz))) for(int j = 1; j < k; j++){
            zz += 9;
            if(black&(1ULL<<zz)) continue;
            if(white&(1ULL<<zz)){
                black &= ~(bit_mask[z][1][j]);
                white |= bit_mask[z][1][j];
                /*
                for(int u = 0; u < j; u++){
                    zz -= 9;
                    black &= ~(1ULL<<zz);
                    white |= (1ULL<<zz);
                }
                */
            }
            break;
        }
        zz = z+1; k = 7-w;
        if(k > 1 && (black&(1ULL<<zz))) for(int j = 1; j < k; j++){
            zz++;
            if(black&(1ULL<<zz)) continue;
            if(white&(1ULL<<zz)){
                black &= ~(bit_mask[z][2][j]);
                white |= bit_mask[z][2][j];
                /*
                for(int u = 0; u < j; u++){
                    zz--;
                    black &= ~(1ULL<<zz);
                    white |= (1ULL<<zz);
                }
                */
            }
            break;
        }
        zz = z-7; k = min(h,7-w);
        if(k > 1 && (black&(1ULL<<zz))) for(int j = 1; j < k; j++){
            zz -= 7;
            if(black&(1ULL<<zz)) continue;
            if(white&(1ULL<<zz)){
                black &= ~(bit_mask[z][3][j]);
                white |= bit_mask[z][3][j];
                /*
                for(int u = 0; u < j; u++){
                    zz += 7;
                    black &= ~(1ULL<<zz);
                    white |= (1ULL<<zz);
                }
                */
            }
            break;
        }
        zz = z-8;
        if(h > 1 && (black&(1ULL<<zz))) for(int j = 1; j < h; j++){
            zz -= 8;
            if(black&(1ULL<<zz)) continue;
            if(white&(1ULL<<zz)){
                black &= ~(bit_mask[z][4][j]);
                white |= bit_mask[z][4][j];
                /*
                for(int u = 0; u < j; u++){
                    zz += 8;
                    black &= ~(1ULL<<zz);
                    white |= (1ULL<<zz);
                }
                */
            }
            break;
        }
        zz = z-9; k = min(h,w);
        if(k > 1 && (black&(1ULL<<zz))) for(int j = 1; j < k; j++){
            zz -= 9;
            if(black&(1ULL<<zz)) continue;
            if(white&(1ULL<<zz)){
                black &= ~(bit_mask[z][5][j]);
                white |= bit_mask[z][5][j];
                /*
                for(int u = 0; u < j; u++){
                    zz += 9;
                    black &= ~(1ULL<<zz);
                    white |= (1ULL<<zz);
                }
                */
            }
            break;
        }
        zz = z-1;
        if(w > 1 && (black&(1ULL<<zz))) for(int j = 1; j < w; j++){
            zz--;
            if(black&(1ULL<<zz)) continue;
            if(white&(1ULL<<zz)){
                black &= ~(bit_mask[z][6][j]);
                white |= bit_mask[z][6][j];
                /*
                for(int u = 0; u < j; u++){
                    zz++;
                    black &= ~(1ULL<<zz);
                    white |= (1ULL<<zz);
                }
                */
            }
            break;
        }
        zz = z+7; k = min(7-h,w);
        if(k > 1 && (black&(1ULL<<zz))) for(int j = 1; j < k; j++){
            zz += 7;
            if(black&(1ULL<<zz)) continue;
            if(white&(1ULL<<zz)){
                black &= ~(bit_mask[z][7][j]);
                white |= bit_mask[z][7][j];
                /*
                for(int u = 0; u < j; u++){
                    zz -= 7;
                    black &= ~(1ULL<<zz);
                    white |= (1ULL<<zz);
                }
                */
            }
            break;
        }

        return (pre_white != white);
    }
}

bool hash_change_board(ull& black, ull& white, bool now, int h, int w, ull& hasher){
#ifdef DEBUG
    hash_change_board_counter++;
#endif
    hasher ^= random_number[64*2];
    int id = (h<<3)+w;
    bool ret = false;
    if(now){
        black |= (1ULL<<id);
        hasher ^= random_number[id*2];
        int hh = h+1, ww = w;
        if(hh <= 6 && (white&(1ULL<<((hh<<3)+ww)))){
            for(int j = 1;; j++){
                hh++;
                if(hh >= 8) break;
                if(white&(1ULL<<((hh<<3)+ww))) continue;
                if(black&(1ULL<<((hh<<3)+ww))){
                    ret = true;
                    for(int u = 0; u < j; u++){
                        hh--;
                        int new_id = (hh<<3)+ww;
                        white &= ~(1ULL<<new_id);
                        black |= (1ULL<<new_id);
                        hasher ^= random_number[new_id*2+1];
                        hasher ^= random_number[new_id*2];
                    }
                }
                break;
            }
        }
        hh = h+1; ww = w+1;
        if(hh <= 6 && ww <= 6 && (white&(1ULL<<((hh<<3)+ww)))){
            for(int j = 1;; j++){
                hh++; ww++;
                if(hh >= 8 || ww >= 8) break;
                if(white&(1ULL<<((hh<<3)+ww))) continue;
                if(black&(1ULL<<((hh<<3)+ww))){
                    ret = true;
                    for(int u = 0; u < j; u++){
                        hh--; ww--;
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
        hh = h; ww = w+1;
        if(ww <= 6 && (white&(1ULL<<((hh<<3)+ww)))){
            for(int j = 1;; j++){
                ww++;
                if(ww >= 8) break;
                if(white&(1ULL<<((hh<<3)+ww))) continue;
                if(black&(1ULL<<((hh<<3)+ww))){
                    ret = true;
                    for(int u = 0; u < j; u++){
                        ww--;
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
        hh = h-1; ww = w+1;
        if(hh >= 1 && ww <= 6 && (white&(1ULL<<((hh<<3)+ww)))){
            for(int j = 1;; j++){
                hh--; ww++;
                if(hh < 0 || ww >= 8) break;
                if(white&(1ULL<<((hh<<3)+ww))) continue;
                if(black&(1ULL<<((hh<<3)+ww))){
                    ret = true;
                    for(int u = 0; u < j; u++){
                        hh++; ww--;
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
        hh = h-1; ww = w;
        if(hh >= 1 && (white&(1ULL<<((hh<<3)+ww)))){
            for(int j = 1;; j++){
                hh--;
                if(hh < 0) break;
                if(white&(1ULL<<((hh<<3)+ww))) continue;
                if(black&(1ULL<<((hh<<3)+ww))){
                    ret = true;
                    for(int u = 0; u < j; u++){
                        hh++;
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
        hh = h-1; ww = w-1;
        if(hh >= 1 && ww >= 1 && (white&(1ULL<<((hh<<3)+ww)))){
            for(int j = 1;; j++){
                hh--; ww--;
                if(hh < 0 || ww < 0) break;
                if(white&(1ULL<<((hh<<3)+ww))) continue;
                if(black&(1ULL<<((hh<<3)+ww))){
                    ret = true;
                    for(int u = 0; u < j; u++){
                        hh++; ww++;
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
        hh = h; ww = w-1;
        if(ww >= 1 && (white&(1ULL<<((hh<<3)+ww)))){
            for(int j = 1;; j++){
                ww--;
                if(ww < 0) break;
                if(white&(1ULL<<((hh<<3)+ww))) continue;
                if(black&(1ULL<<((hh<<3)+ww))){
                    ret = true;
                    for(int u = 0; u < j; u++){
                        ww++;
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
        hh = h+1; ww = w-1;
        if(hh <= 6 && ww >= 1 && (white&(1ULL<<((hh<<3)+ww)))){
            for(int j = 1;; j++){
                hh++; ww--;
                if(hh >= 8 || ww < 0) break;
                if(white&(1ULL<<((hh<<3)+ww))) continue;
                if(black&(1ULL<<((hh<<3)+ww))){
                    ret = true;
                    for(int u = 0; u < j; u++){
                        hh--; ww++;
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
        /*
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
                        hasher ^= random_number[new_id*2];
                        hasher ^= random_number[new_id*2+1];
                    }
                }
                break;
            }
        }
        */
        int hh = h+1, ww = w;
        if(hh <= 6 && (black&(1ULL<<((hh<<3)+ww)))){
            for(int j = 1;; j++){
                hh++;
                if(hh >= 8) break;
                if(black&(1ULL<<((hh<<3)+ww))) continue;
                if(white&(1ULL<<((hh<<3)+ww))){
                    ret = true;
                    for(int u = 0; u < j; u++){
                        hh--;
                        int new_id = (hh<<3)+ww;
                        black &= ~(1ULL<<new_id);
                        white |= (1ULL<<new_id);
                        hasher ^= random_number[new_id*2];
                        hasher ^= random_number[new_id*2+1];
                    }
                }
                break;
            }
        }
        hh = h+1; ww = w+1;
        if(hh <= 6 && ww <= 6 && (black&(1ULL<<((hh<<3)+ww)))){
            for(int j = 1;; j++){
                hh++; ww++;
                if(hh >= 8 || ww >= 8) break;
                if(black&(1ULL<<((hh<<3)+ww))) continue;
                if(white&(1ULL<<((hh<<3)+ww))){
                    ret = true;
                    for(int u = 0; u < j; u++){
                        hh--; ww--;
                        int new_id = (hh<<3)+ww;
                        black &= ~(1ULL<<new_id);
                        white |= (1ULL<<new_id);
                        hasher ^= random_number[new_id*2];
                        hasher ^= random_number[new_id*2+1];
                    }
                }
                break;
            }
        }
        hh = h; ww = w+1;
        if(ww <= 6 && (black&(1ULL<<((hh<<3)+ww)))){
            for(int j = 1;; j++){
                ww++;
                if(ww >= 8) break;
                if(black&(1ULL<<((hh<<3)+ww))) continue;
                if(white&(1ULL<<((hh<<3)+ww))){
                    ret = true;
                    for(int u = 0; u < j; u++){
                        ww--;
                        int new_id = (hh<<3)+ww;
                        black &= ~(1ULL<<new_id);
                        white |= (1ULL<<new_id);
                        hasher ^= random_number[new_id*2];
                        hasher ^= random_number[new_id*2+1];
                    }
                }
                break;
            }
        }
        hh = h-1; ww = w+1;
        if(hh >= 1 && ww <= 6 && (black&(1ULL<<((hh<<3)+ww)))){
            for(int j = 1;; j++){
                hh--; ww++;
                if(hh < 0 || ww >= 8) break;
                if(black&(1ULL<<((hh<<3)+ww))) continue;
                if(white&(1ULL<<((hh<<3)+ww))){
                    ret = true;
                    for(int u = 0; u < j; u++){
                        hh++; ww--;
                        int new_id = (hh<<3)+ww;
                        black &= ~(1ULL<<new_id);
                        white |= (1ULL<<new_id);
                        hasher ^= random_number[new_id*2];
                        hasher ^= random_number[new_id*2+1];
                    }
                }
                break;
            }
        }
        hh = h-1; ww = w;
        if(hh >= 1 && (black&(1ULL<<((hh<<3)+ww)))){
            for(int j = 1;; j++){
                hh--;
                if(hh < 0) break;
                if(black&(1ULL<<((hh<<3)+ww))) continue;
                if(white&(1ULL<<((hh<<3)+ww))){
                    ret = true;
                    for(int u = 0; u < j; u++){
                        hh++;
                        int new_id = (hh<<3)+ww;
                        black &= ~(1ULL<<new_id);
                        white |= (1ULL<<new_id);
                        hasher ^= random_number[new_id*2];
                        hasher ^= random_number[new_id*2+1];
                    }
                }
                break;
            }
        }
        hh = h-1; ww = w-1;
        if(hh >= 1 && ww >= 1 && (black&(1ULL<<((hh<<3)+ww)))){
            for(int j = 1;; j++){
                hh--; ww--;
                if(hh < 0 || ww < 0) break;
                if(black&(1ULL<<((hh<<3)+ww))) continue;
                if(white&(1ULL<<((hh<<3)+ww))){
                    ret = true;
                    for(int u = 0; u < j; u++){
                        hh++; ww++;
                        int new_id = (hh<<3)+ww;
                        black &= ~(1ULL<<new_id);
                        white |= (1ULL<<new_id);
                        hasher ^= random_number[new_id*2];
                        hasher ^= random_number[new_id*2+1];
                    }
                }
                break;
            }
        }
        hh = h; ww = w-1;
        if(ww >= 1 && (black&(1ULL<<((hh<<3)+ww)))){
            for(int j = 1;; j++){
                ww--;
                if(ww < 0) break;
                if(black&(1ULL<<((hh<<3)+ww))) continue;
                if(white&(1ULL<<((hh<<3)+ww))){
                    ret = true;
                    for(int u = 0; u < j; u++){
                        ww++;
                        int new_id = (hh<<3)+ww;
                        black &= ~(1ULL<<new_id);
                        white |= (1ULL<<new_id);
                        hasher ^= random_number[new_id*2];
                        hasher ^= random_number[new_id*2+1];
                    }
                }
                break;
            }
        }
        hh = h+1; ww = w-1;
        if(hh <= 6 && ww >= 1 && (black&(1ULL<<((hh<<3)+ww)))){
            for(int j = 1;; j++){
                hh++; ww--;
                if(hh >= 8 || ww < 0) break;
                if(black&(1ULL<<((hh<<3)+ww))) continue;
                if(white&(1ULL<<((hh<<3)+ww))){
                    ret = true;
                    for(int u = 0; u < j; u++){
                        hh--; ww++;
                        int new_id = (hh<<3)+ww;
                        black &= ~(1ULL<<new_id);
                        white |= (1ULL<<new_id);
                        hasher ^= random_number[new_id*2];
                        hasher ^= random_number[new_id*2+1];
                    }
                }
                break;
            }
        }
    }
    return ret;
}
