#ifndef GENERATE
#define GENERATE

#include "board.h"

#include <vector>
using namespace std;

typedef int_least8_t direction;

direction pinnedDirection(Board b, Square s);
bool isEnPassantAdjacent(Square s, Square ep);
bool isPawnBlocked(Board b, Square s);
bool isPinned(Board b, Square s);
moves makeMoves(square x, square y, side t, piece promote);
vector<string> generate(Board b, Square s, piece p, side t);
vector<string> returnMoves(Board b);

#endif