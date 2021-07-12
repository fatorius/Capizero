#include "attacks.h"

#include <cstdlib>
using namespace std;

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
    b.colorflip();
}

bitset<5> kingAttackers(Board b){
    bitset<5> attackers = 0x0;

    Square king = b.getKingSquare();
    king.y = 7 - king.y;
    
    if (pawnAttacks(b, king) > 0){
        attackers[PAWN] = 1;
    }
    if (knightAttacks(b, king)){
        attackers[KNIGHT] = 1;
    }
    if (bishopAttacks(b, king)){
        attackers[BISHOP] = 1;
    }
    if (rookAttacks(b, king)){
        attackers[ROOK] = 1;
    }
    if (queenAttacks(b, king)){
        attackers[QUEEN] = 1;
    }

    b.colorflip();

    return attackers;
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

bool doesPawnAttacks(Board b, Square target, Square originalSquare){
    if (b.getPiece(originalSquare.x - 1, originalSquare.y + 1) ==  whitePawn){
        return true;
    }
    if (b.getPiece(originalSquare.x + 1, originalSquare.y + 1) == whitePawn){
        return true;
    }

    return false;
}

bool doesKnightAttacks(Board b, Square target, Square originalSquare){
    int_least8_t attacks = 0;

    for (int_fast8_t i = 0; i < 8; i++){
        int_fast8_t ix = ((i > 3) + 1) * (((i % 4) > 1) * 2 - 1);
        int_fast8_t iy = (2 - (i > 3)) * ((i % 2 == 0) * 2 - 1);

        piece p = b.getPiece(originalSquare.x + ix, originalSquare.y + iy);

        Square targetSquare(originalSquare.x + ix, originalSquare.y + iy);

        if (p == whiteKnight and !isPinned(b, targetSquare)){
            return true;
        }
    }

    return false;
}

bool doesBishopAttacks(Board b, Square target, Square originalSquare){
    int_least8_t attacks = 0;

    for (int_fast8_t i = 0; i < 4; i++){
        int_fast8_t ix = ((i > 1) * 2 - 1);
        int_fast8_t iy = ((i % 2 == 0) * 2 - 1);
    
        for (int_fast8_t d = 1; d < 8; d++){
            Square pieceSquare(originalSquare.x + (d * ix), originalSquare.y + (d * iy));
            piece p = b.getPiece(pieceSquare);

            if (p == whiteBishop){

                direction dir = pinnedDirection(b, pieceSquare);
                if (dir == NOTPINNED or abs(ix + (iy * 3)) == dir){
                    return true;
                }
            }
            else if (p != noPiece){
                break;
            }
        }
    }
    return false;
}

bool doesRookAttacks(Board b, Square target, Square originalSquare){
     int_least8_t attacks = 0;

    for (int_fast8_t i = 0; i < 4; i++){
        int_fast8_t ix = (i == 0 ? -1 : i == 1 ? 1 : 0);
        int_fast8_t iy = (i == 2 ? -1 : i == 3 ? 1 : 0);
        
        for (int_fast8_t d = 1; d < 8; d++){
            Square pieceSquare(originalSquare.x + (d * ix), originalSquare.y + (d * iy));
            piece p = b.getPiece(pieceSquare);

            if (p == whiteRook){
                direction dir = pinnedDirection(b, pieceSquare);
                if (dir == NOTPINNED or abs(ix + (iy * 3)) == dir){
                    return true;
                }
            }
            else if (p != noPiece){
                break;
            }
        }
    }

    return false;
}

bool doesQueenAttacks(Board b, Square target, Square originalSquare){
    int_least8_t attacks = 0;

    for (int_fast8_t i = 0; i < 8; i++){
        int_fast8_t ix = (i + (i > 3)) % 3 - 1;
        int_fast8_t iy = (((i + (i > 3)) / 3) << 0) - 1;

        for (int_fast8_t d = 1; d < 8; d++){
            Square pieceSquare(originalSquare.x + (d * ix), originalSquare.y + (d * iy));
            piece p = b.getPiece(pieceSquare);

            if (p == whiteQueen){
                direction dir = pinnedDirection(b, pieceSquare);
                if (dir == 0 or abs(ix + (iy *3)) == dir){
                    return true;
                }   
            }
            else if (p != noPiece){
                break;
            }
        }
    }
    return false;
}

bool doesKingAttacks(Board b, Square target, Square originalSquare){
    for (int_fast8_t i = 0; i < 8; i++) {
        int_fast8_t ix = (i + (i > 3)) % 3 - 1;
        int_fast8_t iy = (((i + (i > 3)) / 3) << 0) - 1;
        
        if (b.getPiece(originalSquare.x + ix, originalSquare.y + iy) == whiteKing){
            return true;
        }
    }
    return false;
}

int_least8_t pawnAttacks(Board b, Square s){
    int_least8_t attacks = 0;

    if (b.getPiece(s.x - 1, s.y - 1) ==  whitePawn){
        attacks++;
    }
    if (b.getPiece(s.x + 1, s.y - 1) == whitePawn){
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
            else if (p != noPiece){
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
            else if (p != noPiece){
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

int_least8_t kingAttacks(Board b, Square s){
    for (int_fast8_t i = 0; i < 8; i++) {
        int_fast8_t ix = (i + (i > 3)) % 3 - 1;
        int_fast8_t iy = (((i + (i > 3)) / 3) << 0) - 1;
        
        if (b.getPiece(s.x + ix, s.y + iy) == whiteKing){
            return 1;
        }
    }
    return 0;
}

int_least8_t attacks(Board b, Square s){
    int_least8_t attacks = 0;

    attacks += pawnAttacks(b, s);
    attacks += knightAttacks(b, s);
    attacks += bishopAttacks(b, s);
    attacks += rookAttacks(b, s);
    attacks += queenAttacks(b, s);
    attacks += kingAttacks(b, s);

    return attacks;
}

Square attackerForKing(Board b, Square s){
    if (b.getPiece(s.x - 1, s.y + 1) ==  whitePawn){
        return Square(s.x - 1, s.y + 1);
    }
    if (b.getPiece(s.x + 1, s.y + 1) == whitePawn){
        return Square(s.x - 1, s.y + 1);
    }

    for (int_fast8_t i = 0; i < 8; i++){
        int_fast8_t ix = ((i > 3) + 1) * (((i % 4) > 1) * 2 - 1);
        int_fast8_t iy = (2 - (i > 3)) * ((i % 2 == 0) * 2 - 1);

        piece p = b.getPiece(s.x + ix, s.y + iy);

        Square targetSquare(s.x + ix, s.y + iy);

        if (p == whiteKnight and !isPinned(b, targetSquare)){
            return Square(s.x + ix, s.y + iy);
        }
    }

    for (int_fast8_t i = 0; i < 4; i++){
        int_fast8_t ix = ((i > 1) * 2 - 1);
        int_fast8_t iy = ((i % 2 == 0) * 2 - 1);
    
        for (int_fast8_t d = 1; d < 8; d++){
            Square pieceSquare(s.x + (d * ix), s.y + (d * iy));
            piece p = b.getPiece(pieceSquare);

            if (p == whiteBishop){

                direction dir = pinnedDirection(b, pieceSquare);
                if (dir == NOTPINNED or abs(ix + (iy * 3)) == dir){
                    return Square(s.x + (d * ix), s.y + (d * iy));
                }
            }
            else if (p != noPiece and p != whiteQueen and p != blackQueen){
                break;
            }
        }
    }

    for (int_fast8_t i = 0; i < 4; i++){
        int_fast8_t ix = (i == 0 ? -1 : i == 1 ? 1 : 0);
        int_fast8_t iy = (i == 2 ? -1 : i == 3 ? 1 : 0);
        
        for (int_fast8_t d = 1; d < 8; d++){
            Square pieceSquare(s.x + (d * ix), s.y + (d * iy));
            piece p = b.getPiece(pieceSquare);

            if (p == whiteRook){
                direction dir = pinnedDirection(b, pieceSquare);
                if (dir == NOTPINNED or abs(ix + (iy * 3)) == dir){
                    return Square(s.x + (d * ix), s.y + (d * iy));
                }
            }
            else if (p != noPiece and p != whiteQueen and p != blackQueen){
                break;
            }
        }
    }

    for (int_fast8_t i = 0; i < 8; i++){
        int_fast8_t ix = (i + (i > 3)) % 3 - 1;
        int_fast8_t iy = (((i + (i > 3)) / 3) << 0) - 1;

        for (int_fast8_t d = 1; d < 8; d++){
            Square pieceSquare(s.x + (d * ix), s.y + (d * iy));
            piece p = b.getPiece(pieceSquare);

            if (p == whiteQueen){
                direction dir = pinnedDirection(b, pieceSquare);
                if (dir == 0 or abs(ix + (iy *3)) == dir){
                    return Square(s.x + (d * ix), s.y + (d * iy));
                }   
            }
            else if (p != noPiece){
                break;
            }
        }
    }
}