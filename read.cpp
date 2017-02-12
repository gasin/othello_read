#include "global.h"
#include "search.h"
#include "hash.h"
#include "inout.h"

int main(){
    chrono::system_clock::time_point start, end;
    start = chrono::system_clock::now();
    
    init_random();

    bool first_turn; //1..black, 0..white
    bitset<64> black(0), white(0);
    input(first_turn, black, white);
    
    int result = firstsearch(black, white, first_turn);
    
    output(result);

    end = chrono::system_clock::now();
    double elapsed = chrono::duration_cast<chrono::milliseconds>(end-start).count();
    elapsed /= 1000.0;
    printf("%f\n",elapsed);
}
