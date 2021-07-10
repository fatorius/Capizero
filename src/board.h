#ifndef BOARD
#define BOARD

#include <string>
#include <bitset>
using namespace std;

#define INITIAL_POSITION "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

#define NUMBER_OF_SQUARES 63
#define NUMBER_OF_RANKS 8
#define NUMBER_OF_FILES 8

#define WHITE true
#define BLACK false

#define WHITEKINGSIDE 0
#define WHITEQUEENSIDE 1
#define BLACKKINGSIDE 2
#define BLACKQUEENSIDE 3

#define NOCASTLING 0x0

typedef bool side;
typedef int_least8_t piece;
typedef int_fast8_t coordinate;
typedef int_least8_t square;
typedef string moves;
typedef string squareString; 

const piece outOfSquare = -1;
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

coordinate getRank(string s);
coordinate getFile(string s);

bool isWhitePiece(piece p);
bool isBlackPiece(piece p);

piece invertColor(piece p);

string pieceToString(piece piece);

class Square{
    public:
        Square(squareString s);
        Square(coordinate c1, coordinate c2);
        coordinate x;
        coordinate y;

        square convert();
        squareString getString();

    private: 
        string coordToFile();
        string coordToRank();
};

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

        side turn;
        squareString enPassantSquare;

        bitset<4> castlingSides = 0x0;

        int halfmoves;
        int fullmoves;

        void setPosition(string newFen);
        void printBoard();
        void makeMove(moves san);
        void colorflip();
        piece getPiece(square s);
        piece getPiece(Square sq);
        piece getPiece(coordinate x, coordinate y);
        Square getKingSquare();

        string fen();

    private:
        void setCastlingSides(string fen);
        void setMoveAmount(string fen);
        void setPiece(Square s, piece target);
        void setEnPassantSquare(string fen);
        void setEnPassantSquareFromMove(string fen);
        square coordinateToSquare(coordinate x, coordinate y);
        piece getPromotedPiece(char p);
}; 

#endif