#ifndef GLOBAL_H
#define GLOBAL_H
//#define DEBUG

#include <iostream>
#include <cmath>
#include <random>
#include <unordered_map>
#include <chrono>
#include <string.h>
#include <algorithm>
#define rep(i,n) for(int i = 0; i < n; i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> P;

static const int INF = 10000;
static const int EMPTY_AREA = 30;
static const int HASH_DEPTH = 12;
static const int RANDOM_NUMBER = 300;
static const int dh[8] = {1,1,0,-1,-1,-1,0,1};
static const int dw[8] = {0,1,1,1,0,-1,-1,-1}; 

#ifdef DEBUG
extern ll hash_search_counter;
extern ll unhash_search_counter;
extern ll final_search_counter;
extern ll hash_change_board_counter;
extern ll unhash_change_board_counter;
#endif

#endif

