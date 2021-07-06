#ifndef GENERATE
#define GENERATE

#include "board.h"

#include <vector>
using namespace std;

moves makeMoves(square x, square y);
string generate(Square s);
vector<string> returnMoves(Board b);

#endif