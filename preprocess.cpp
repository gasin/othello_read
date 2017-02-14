#include "preprocess.h"

ull bit_mask[64][8][8];

void preprocess(){
    memset(bit_mask,0,sizeof(bit_mask));
    rep(h,8) rep(w,8){
        rep(i,8){
            int hh = h, ww = w;
            rep(j,8){
                hh += dh[i]; ww += dw[i];
                if(hh >= 8 || hh < 0 || ww >= 8 || ww < 0) break;
                bit_mask[h*8+w][i][j+1] |= bit_mask[h*8+w][i][j];
                bit_mask[h*8+w][i][j+1] |= (1ULL<<(hh*8+ww));
            }
        }
    }
}
