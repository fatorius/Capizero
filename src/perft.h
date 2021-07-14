#ifndef PERFT
#define PERFT

#include "board.h"

#include <bits/stdc++.h>
#include <chrono>

using namespace std;

typedef unsigned long long u64;

void calc_perft(Board b);
u64 perft(int depth, Board pos, bool first);


#endif