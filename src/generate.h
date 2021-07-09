#ifndef GENERATE
#define GENERATE

#include "attacks.h"

#include <vector>
using namespace std;

bool isEnPassantAdjacent(Square s, Square ep);
bool isPawnBlocked(Board b, Square s);
moves makeMoves(square x, square y, side t, piece promote);
vector<string> generate(Board b, Square s, piece p, side t);
vector<string> returnMoves(Board b);

#endif