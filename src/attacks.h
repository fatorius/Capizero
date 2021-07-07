#ifndef ATTACKS
#define ATTACKS

#include "board.h"

typedef int_least8_t direction;

bool isPinned(Board b, Square s);
direction pinnedDirection(Board b, Square s);

// checks if that specific piece attacks a given square
bool doesPawnAttacks(Board b, Square target, Square originalSquare);
bool doesKnightAttacks(Board b, Square target, Square originalSquare);
bool doesBishopAttacks(Board b, Square target, Square originalSquare);
bool doesRookAttacks(Board b, Square target, Square originalSquare);
bool doesQueenAttacks(Board b, Square target, Square originalSquare);

int_least8_t pawnAttacks(Board b, Square s);
int_least8_t knightAttacks(Board b, Square s);
int_least8_t bishopAttacks(Board b, Square s);
int_least8_t rookAttacks(Board b, Square s);
int_least8_t queenAttacks(Board b, Square s);
int_least8_t attacks(Board b, Square s);

#endif