#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <bitset>
using namespace std;

#define INITIAL_POSITION "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

#define NO_PIECE 0

#define whitePawn 1
#define blackPawn 2
#define whiteKnight 3
#define blackKnight 4
#define whiteBishop 5
#define blackBishop 6
#define whiteRook 7
#define blackRook 8
#define whiteQueen 9
#define blackQueen 10
#define whiteKing 11
#define blackKing 12

#define NUMBER_OF_SQUARES 64
#define NUMBER_OF_RANKS 8
#define NUMBER_OF_FILES 8

#define WHITE true;
#define BLACK false;

typedef bool side;
typedef bitset<4> piece;
typedef int_fast8_t coordinate;
typedef int_least8_t square;

class Board{

    public:
        Board(string fen = INITIAL_POSITION);
        string currentPosition;

        bitset<NUMBER_OF_SQUARES> whitePawns;
        bitset<NUMBER_OF_SQUARES> blackPawns;
        bitset<NUMBER_OF_SQUARES> whiteKnights;
        bitset<NUMBER_OF_SQUARES> blackKnights;
        bitset<NUMBER_OF_SQUARES> whiteBishops;
        bitset<NUMBER_OF_SQUARES> blackBishops;
        bitset<NUMBER_OF_SQUARES> whiteRooks;
        bitset<NUMBER_OF_SQUARES> blackRooks;
        bitset<NUMBER_OF_SQUARES> whiteQueens;
        bitset<NUMBER_OF_SQUARES> blackQueens;
        bitset<NUMBER_OF_SQUARES> whiteKings;
        bitset<NUMBER_OF_SQUARES> blackKings;

        void setPosition(string newFen);
        piece getPiece(coordinate x, coordinate y);

        side side;

        bitset<4> castlingSides = 0x0;

    private:
        square coordinateToSquare(coordinate x, coordinate y);
        void setCastlingSides(string fen);
};

#endif