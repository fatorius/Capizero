#ifndef PERFT
#define PERFT

#include "generate.h"

using namespace std;

typedef unsigned long long u64;

void calc_perft(Board b);
u64 perft(int depth, Board pos, bool first);


#endif