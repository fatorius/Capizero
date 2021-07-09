#include "attacks.h"

#include <cstdlib>
using namespace std;

#define NOTPINNED 0
#define HORIZONTALPIN 1
#define TOPLEFTTOBOTTOMRIGHT 2
#define VERTICALPIN 3
#define TOPRIGHTTOBOTTOMLEFT 4

bool isPinned(Board b, Square s){
    piece p = b.getPiece(s);
    if (!isWhitePiece(p)){
        return false;
    }
    else if (pinnedDirection(b, s) != 0){
        return true;
    }
    else{
        return false;
    }
}

bool isCheck(Board b){
    Square king = b.getKingSquare();
    king.y = 7 - king.y;
    b.colorflip();
    if (attacks(b, king) != 0){
        return true;
    }
    else{
        return false;
    }
}

direction pinnedDirection(Board b, Square s){
    for (int_fast8_t i = 0; i <  8; i++){
        int_fast8_t ix = (i + (i > 3)) % 3 - 1;
        int_fast8_t iy = (((i + (i > 3)) / 3) << 0) - 1;
        bool king = false;
        for (int_fast8_t d = 1; d < 8; d++){
            piece p = b.getPiece(s.x + (d * ix), s.y + (d * iy));
            if (p == whiteKing){
                king = true;
            }
            if (p != noPiece){
                break;
            }
        }
        if (king){
            for (int_fast8_t d = 1; d < 8; d++){
                piece p = b.getPiece(s.x - (d * ix), s.y - (d * iy));

                if (p == blackQueen or 
                    (p == blackBishop and ix * iy != 0) or
                    (p == blackRook and ix * iy == 0)){
                        return abs(ix + (iy * 3));
                }
                if (p != noPiece){
                    break;
                }
            }
        }
    }
    return 0;
}

int_least8_t pawnAttacks(Board b, Square s){
    int_least8_t attacks = 0;

    if (b.getPiece(s.x - 1, s.y + 1) ==  whitePawn){
        attacks++;
    }
    if (b.getPiece(s.x + 1, s.y + 1) == whitePawn){
        attacks++;
    }

    return attacks;
}

int_least8_t knightAttacks(Board b, Square s){
    int_least8_t attacks = 0;

    for (int_fast8_t i = 0; i < 8; i++){
        int_fast8_t ix = ((i > 3) + 1) * (((i % 4) > 1) * 2 - 1);
        int_fast8_t iy = (2 - (i > 3)) * ((i % 2 == 0) * 2 - 1);

        piece p = b.getPiece(s.x + ix, s.y + iy);

        Square targetSquare(s.x + ix, s.y + iy);

        if (p == whiteKnight and !isPinned(b, targetSquare)){
            attacks++;
        }
    }

    return attacks;    
}

int_least8_t bishopAttacks(Board b, Square s){
    int_least8_t attacks = 0;

    for (int_fast8_t i = 0; i < 4; i++){
        int_fast8_t ix = ((i > 1) * 2 - 1);
        int_fast8_t iy = ((i % 2 == 0) * 2 - 1);
    
        for (int_fast8_t d = 1; d < 8; d++){
            Square pieceSquare(s.x + (d * ix), s.y + (d * iy));
            piece p = b.getPiece(pieceSquare);

            if (p == whiteBishop){

                direction dir = pinnedDirection(b, pieceSquare);
                if (dir == NOTPINNED or abs(ix + (iy * 3)) == dir){
                    attacks++;
                }
            }
            else if (p != noPiece and p != whiteQueen and p != blackQueen){
                break;
            }
        }
    }
    return attacks;
}

int_least8_t rookAttacks(Board b, Square s){
     int_least8_t attacks = 0;

    for (int_fast8_t i = 0; i < 4; i++){
        int_fast8_t ix = (i == 0 ? -1 : i == 1 ? 1 : 0);
        int_fast8_t iy = (i == 2 ? -1 : i == 3 ? 1 : 0);
        
        for (int_fast8_t d = 1; d < 8; d++){
            Square pieceSquare(s.x + (d * ix), s.y + (d * iy));
            piece p = b.getPiece(pieceSquare);

            if (p == whiteRook){
                direction dir = pinnedDirection(b, pieceSquare);
                if (dir == NOTPINNED or abs(ix + (iy * 3)) == dir){
                    attacks++;
                }
            }
            else if (p != noPiece and p != whiteQueen and p != blackQueen){
                break;
            }
        }
    }

    return attacks;
}

int_least8_t queenAttacks(Board b, Square s){
    int_least8_t attacks = 0;

    for (int_fast8_t i = 0; i < 8; i++){
        int_fast8_t ix = (i + (i > 3)) % 3 - 1;
        int_fast8_t iy = (((i + (i > 3)) / 3) << 0) - 1;

        for (int_fast8_t d = 1; d < 8; d++){
            Square pieceSquare(s.x + (d * ix), s.y + (d * iy));
            piece p = b.getPiece(pieceSquare);

            if (p == whiteQueen){
                direction dir = pinnedDirection(b, pieceSquare);
                if (dir == 0 or abs(ix + (iy *3)) == dir){
                    attacks++;
                }   
            }
            else if (p != noPiece){
                break;
            }
        }
    }
    return attacks;
}

int_least8_t attacks(Board b, Square s){
    int_least8_t attacks = 0;

    attacks += pawnAttacks(b, s);
    attacks += knightAttacks(b, s);
    attacks += bishopAttacks(b, s);
    attacks += rookAttacks(b, s);
    attacks += queenAttacks(b, s);

    return attacks;
}