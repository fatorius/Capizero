#include "generate.h"

#include "attacks.h"

#include <cstdlib>
#include <iostream>
using namespace std;

#define NOTPINNED 0
#define HORIZONTALPIN 1
#define TOPLEFTTOBOTTOMRIGHT 2
#define VERTICALPIN 3
#define TOPRIGHTTOBOTTOMLEFT 4

bool isPawnBlocked(Board b, Square s){
    if (b.getPiece(s.x, s.y+1) != noPiece){
        return true;
    }
    else{
        return false;
    }
}

moves makeMoves(Square x, Square y, side t, piece promote=noPiece){
    if (t == WHITE){
        string base = x.getString() + y.getString();
        if (promote != noPiece){
            base += pieceToString(promote);
        }
        return base;
    }
    else{
        x.y = 7-x.y;
        y.y = 7-y.y;
        string base = x.getString() + y.getString();
        if (promote != noPiece){
            base += pieceToString(invertColor(promote));
        }
        return base;
    }
}

vector<string> generate(Board b, Square s, piece p, side t){
    vector<string> array;
    direction pin = pinnedDirection(b, s);

    switch (p){
        case whitePawn:
            // avanços
            if (!isPawnBlocked(b, s) and (pin == VERTICALPIN or pin == NOTPINNED)){
                Square dest(s.x, s.y+1);
                if (s.y == 6){
                    for (int_fast8_t pie = 1; pie <= 11; pie += 2){
                        array.push_back(makeMoves(s, dest, t, pie));
                    }
                }
                else{ 
                    array.push_back(makeMoves(s, dest, t));
                }
                if (s.y == 1 and b.getPiece(s.x, s.y+2) == noPiece){
                    Square dest2(s.x, s.y+2);
                    array.push_back(makeMoves(s, dest2, t));
                }
            }

            // captura
            if (isBlackPiece(b.getPiece(s.x+1, s.y+1)) and (pin == TOPRIGHTTOBOTTOMLEFT or pin == NOTPINNED)){
                Square cap1(s.x+1, s.y+1);
                if (s.y == 6){
                    for (int pie = 1; pie <= 11; pie += 2){
                        array.push_back(makeMoves(s, cap1, t, pie));
                    }
                }
                else{    
                    array.push_back(makeMoves(s, cap1, t));
                }
            }
            if (isBlackPiece(b.getPiece(s.x-1, s.y+1)) and (pin == TOPLEFTTOBOTTOMRIGHT or pin == NOTPINNED)){
                Square cap2(s.x-1, s.y+1);
                if (s.y == 6){
                    for (int pie = 1; pie <= 11; pie += 2){
                        array.push_back(makeMoves(s, cap2, t, pie));
                    }
                }
                else{
                    array.push_back(makeMoves(s, cap2, t));
                }
            }

            // en passant
            if (b.enPassantSquare != "-"){   
                Square ep(b.enPassantSquare);
                ep.y = 5;
                if (s.x+1 == ep.x and s.y+1 == ep.y and b.getPiece(s.x+1, s.y) == blackPawn and (pin == TOPRIGHTTOBOTTOMLEFT or pin == NOTPINNED)){
                    array.push_back(makeMoves(s, ep, t));
                }
                else if (s.x-1 == ep.x and s.y+1 == ep.y and b.getPiece(s.x-1, s.y) == blackPawn and (pin == TOPLEFTTOBOTTOMRIGHT or pin == NOTPINNED)){
                    array.push_back(makeMoves(s, ep, t));
                }
            }
            break;

        case whiteKnight:
            if (pin != NOTPINNED){
                break;
            }
            for (int_fast8_t i = 0; i < 8; i++){
                int_fast8_t ix = ((i > 3) + 1) * (((i % 4) > 1) * 2 - 1);
                int_fast8_t iy = (2 - (i > 3)) * ((i % 2 == 0) * 2 - 1);

                Square aS(s.x + ix, s.y + iy);
                piece attackedPiece = b.getPiece(aS);

                if (!isWhitePiece(attackedPiece) and attackedPiece != outOfSquare){
                    array.push_back(makeMoves(s, aS, t));
                }
            }
            break;

        case whiteBishop:
            for (int_fast8_t i = 0; i < 4; i++){
                int_fast8_t ix = ((i > 1) * 2 - 1);
                int_fast8_t iy = ((i % 2 == 0) * 2 - 1);
            
                for (int_fast8_t d = 1; d < 8; d++){
                    Square bA(s.x + (d * ix), s.y + (d * iy));
                    piece attackedPiece = b.getPiece(bA);

                    if (pin == NOTPINNED or abs(ix + (iy * 3)) == pin){    
                        if (attackedPiece == noPiece){
                            
                            array.push_back(makeMoves(s, bA, t));
                        }
                        else if (isBlackPiece(attackedPiece)){
                            array.push_back(makeMoves(s, bA, t));
                            break;
                        }
                        else{
                            break;
                        }
                    }
                    else{
                        break;
                    }
                }
            }
            break;

        case whiteRook:
            for (int_fast8_t i = 0; i < 4; i++){
                int_fast8_t ix = (i == 0 ? -1 : i == 1 ? 1 : 0);
                int_fast8_t iy = (i == 2 ? -1 : i == 3 ? 1 : 0);
                    
                for (int_fast8_t d = 1; d < 8; d++){
                    Square rA(s.x + (d * ix), s.y + (d * iy));
                    piece attackedPiece = b.getPiece(rA);

                    if (pin == NOTPINNED or abs(ix + (iy * 3)) == pin){    
                        if (attackedPiece == noPiece){
                            
                            array.push_back(makeMoves(s, rA, t));
                        }
                        else if (isBlackPiece(attackedPiece)){
                            array.push_back(makeMoves(s, rA, t));
                            break;
                        }
                        else{
                            break;
                        }
                    }
                    else{
                        break;
                    }
                }
            }
            break;
            
        case whiteQueen:
            for (int_fast8_t i = 0; i < 8; i++){
                int_fast8_t ix = (i + (i > 3)) % 3 - 1;
                int_fast8_t iy = (((i + (i > 3)) / 3) << 0) - 1;

                for (int_fast8_t d = 1; d < 8; d++){
                    Square qA(s.x + (d * ix), s.y + (d * iy));
                    piece attackedPiece = b.getPiece(qA);

                    if (pin == NOTPINNED or abs(ix + (iy * 3)) == pin){    
                        if (attackedPiece == noPiece){
                            
                            array.push_back(makeMoves(s, qA, t));
                        }
                        else if (isBlackPiece(attackedPiece)){
                            array.push_back(makeMoves(s, qA, t));
                            break;
                        }
                        else{
                            break;
                        }
                    }
                    else{
                        break;
                    }
                }
            }
            break;

        case whiteKing:
            b.colorflip();
            
            for (int_fast8_t i = 0; i < 8; i++){
                int_fast8_t ix = (i + (i > 3)) % 3 - 1;
                int_fast8_t iy = (((i + (i > 3)) / 3) << 0) - 1;
                
                Square attackSquare(s.x + ix, 7 - s.y + iy);

                piece attackedPiece = b.getPiece(attackSquare);
                
                if ((attackedPiece == noPiece or isWhitePiece(attackedPiece)) and (attacks(b, Square(attackSquare.x, attackSquare.y)) == 0)){
                    array.push_back(makeMoves(s, Square(attackSquare.x, 7-attackSquare.y), t));
                }
            }
            
            b.colorflip();
            
            if (b.castlingSides != NOCASTLING){
                b.colorflip();
                if (b.turn == WHITE){
                    if (b.castlingSides[WHITEKINGSIDE]){
                        if (b.getPiece(4, 7) == blackKing and b.getPiece(5, 7) == noPiece and b.getPiece(6, 7) == noPiece and
                            attacks(b, Square(5, 7)) == 0 and attacks(b, Square(6, 7)) == 0 and b.getPiece(7,7) == blackRook){
                                array.push_back("o-o");
                        }
                    }
                    if (b.castlingSides[WHITEQUEENSIDE]){
                        if (b.getPiece(4, 7) == blackKing and b.getPiece(1, 7) == noPiece and b.getPiece(2, 7) == noPiece and b.getPiece(3, 7) == noPiece and
                            attacks(b, Square(1, 7)) == 0 and attacks(b, Square(2, 7)) == 0 and attacks(b, Square(3, 7)) == 0 and b.getPiece(0, 7) == blackRook){
                                array.push_back("o-o-o");
                        }
                    }
                }
                else{
                    if (b.castlingSides[BLACKKINGSIDE]){
                        if (b.getPiece(4, 7) == blackKing and b.getPiece(5, 7) == noPiece and b.getPiece(6, 7) == noPiece and
                            attacks(b, Square(5, 7)) == 0 and attacks(b, Square(6, 7)) == 0 and b.getPiece(7,7) == blackRook){
                                array.push_back("o-o");
                        }
                    }
                    if (b.castlingSides[BLACKQUEENSIDE]){
                        if (b.getPiece(4, 7) == blackKing and b.getPiece(1, 7) == noPiece and b.getPiece(2, 7) == noPiece and b.getPiece(3, 7) == noPiece and
                            attacks(b, Square(1, 7)) == 0 and attacks(b, Square(2, 7)) == 0 and attacks(b, Square(3, 7)) == 0 and b.getPiece(0, 7) == blackRook){
                                array.push_back("o-o-o");
                        }
                    }
                }        
                b.colorflip();
            }
            break;
    }

    return array;
}

vector<string> returnMoves(Board b){
    vector<string> moves;
    side t = b.turn;

    if (t == BLACK){
        b.colorflip();
    }

    for (int_fast8_t x = 0; x < 8; x++){
        for (int_fast8_t y = 0; y < 8; y++){
            Square s(x, y);
            piece p = b.getPiece(s);
            if (p == noPiece){
                continue;
            }
            vector<string> tempMoves = generate(b, s, p, t);
            for (unsigned int i = 0; i < tempMoves.size(); i++){
                moves.push_back(tempMoves[i]);
            }
        }
    }

    if (t == BLACK){
        b.colorflip();
    }

    return moves;
}