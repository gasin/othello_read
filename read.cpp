#include "global.h"
#include "search.h"
#include "hash.h"
#include "inout.h"

#ifdef DEBUG
ll hash_search_counter = 0;
ll unhash_search_counter = 0;
ll final_search_counter = 0;
ll hash_change_board_counter = 0;
ll unhash_change_board_counter = 0;
#endif

int main(){
    chrono::system_clock::time_point start, end;
    start = chrono::system_clock::now();
    
    init_random();

    bool first_turn; //1..black, 0..white
    ull black = 0, white = 0;
    input(first_turn, black, white);
    
    int result;
    if(first_turn) result = firstsearch(black,white);
    else result = firstsearch(white,black);
    
    output(result);

    end = chrono::system_clock::now();
    double elapsed = chrono::duration_cast<chrono::milliseconds>(end-start).count();
    elapsed /= 1000.0;
    printf("time: %f\n",elapsed);
    
#ifdef DEBUG
    //cout << "hash_table: " << hash_table.size() << endl;
    cout << "hash_search_counter: " << hash_search_counter << endl;
    cout << "unhash_search_counter: " << unhash_search_counter << endl;
    cout << "final_search_counter: " << final_search_counter << endl;
    cout << "hash_change_board_counter: " << hash_change_board_counter << endl;
    cout << "unhash_change_board_counter: " << unhash_change_board_counter << endl;
#endif
}
