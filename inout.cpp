#include "inout.h"

void input(bool& first_turn, ull& black, ull& white){
    cin >> first_turn;
    char tmp;
    rep(i,8) rep(j,8){
        cin >> tmp;
        if(tmp == '1'){
            black |= (1ULL<<(i*8+j));
        } else if(tmp == '2'){
            white |= (1ULL<<(i*8+j));
        }
    }
}

void output(int result){
    if(result == INF){
        cout << "Lose" << endl;
        return;
    }
    if(result < 0){
        result *= -1;
        result--;
        cout << "Draw" << endl;
        cout << result/8 << " " << result%8 << endl;
    } else{
        result--;
        cout << "Win" << endl;
        cout << result/8 << " " << result%8 << endl;
    }
}

