#ifndef SEARCH
#define SEARCH

#include "benchmark.h"
#include "board.h"

#include <string>

float minmax(Board b, int depth, float alpha, float beta, bool isWhite);
string search(Board b, int depth);

#endif