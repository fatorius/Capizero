#ifndef ATTACKS
#define ATTACKS

#include "board.h"

#define NOTPINNED 0
#define HORIZONTALPIN 1
#define TOPLEFTTOBOTTOMRIGHT 2
#define VERTICALPIN 3
#define TOPRIGHTTOBOTTOMLEFT 4

#define PAWN 1
#define KNIGHT 2
#define BISHOP 3
#define ROOK 4
#define QUEEN 5

typedef int_least8_t direction;

bool isPinned(Board b, Square s);
direction pinnedDirection(Board b, Square s);

bool isCheck(Board b);

bitset<5> kingAttackers(Board b);

// checks if that specific piece attacks a given square
bool doesPawnAttacks(Board b, Square target, Square originalSquare);
bool doesKnightAttacks(Board b, Square target, Square originalSquare);
bool doesBishopAttacks(Board b, Square target, Square originalSquare);
bool doesRookAttacks(Board b, Square target, Square originalSquare);
bool doesQueenAttacks(Board b, Square target, Square originalSquare);
bool doesKingAttacks(Board b, Square target, Square originalSquare);

int_least8_t pawnAttacks(Board b, Square s);
int_least8_t knightAttacks(Board b, Square s);
int_least8_t bishopAttacks(Board b, Square s);
int_least8_t rookAttacks(Board b, Square s);
int_least8_t queenAttacks(Board b, Square s);
int_least8_t kingAttacks(Board b, Square s);

int_least8_t attacks(Board b, Square s);

Square attackerForKing(Board b, Square s);

#endif