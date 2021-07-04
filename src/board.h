#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <bitset>
using namespace std;

#define INITIAL_POSITION "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

#define NUMBER_OF_SQUARES 64
#define NUMBER_OF_RANKS 8
#define NUMBER_OF_FILES 8

#define WHITE true;
#define BLACK false;

typedef bool side;
typedef int_least8_t piece;
typedef int_fast8_t coordinate;
typedef int_least8_t square;

const piece noPiece = 0;
const piece whitePawn = 1;
const piece blackPawn = 2;
const piece whiteKnight = 3;
const piece blackKnight = 4;
const piece whiteBishop = 5;
const piece blackBishop = 6;
const piece whiteRook = 7;
const piece blackRook = 8;
const piece whiteQueen = 9;
const piece blackQueen = 10;
const piece whiteKing = 11;
const piece blackKing = 12;

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

        side side;

        bitset<4> castlingSides = 0x0;

        int halfmoves;
        int fullmoves;

        void setPosition(string newFen);
        void printBoard();
        piece getPiece(coordinate x, coordinate y);

    private:
        square coordinateToSquare(coordinate x, coordinate y);
        void setCastlingSides(string fen);
        void setMoveAmount(string fen);
        string pieceToString(piece piece);
};

#endif