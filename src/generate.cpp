#include "generate.h"
#include <iostream>
using namespace std;

bool isPawnBlocked(Board b, Square s){
    if (b.getPiece(s.x, s.y+1)){
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
    
    switch (p){
        case whitePawn:
            // avanços
            if (!isPawnBlocked(b, s)){
                Square dest(s.x, s.y+1);
                if (s.y == 6){
                    for (int pie = 1; pie <= 11; pie += 2){
                        array.push_back(makeMoves(s, dest, t, pie));
                    }
                }
                else{ 
                    array.push_back(makeMoves(s, dest, t));
                }
                if (s.y == 1){
                    Square dest2(s.x, s.y+2);
                    array.push_back(makeMoves(s, dest2, t));
                }
            }

            // captura
            if (isBlackPiece(b.getPiece(s.x+1, s.y+1))){
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
            if (isBlackPiece(b.getPiece(s.x-1, s.y+1))){
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
                if (s.x+1 == ep.x and s.y+1 == ep.y and b.getPiece(s.x+1, s.y) == blackPawn){
                    array.push_back(makeMoves(s, ep, t));
                }
                else if (s.x-1 == ep.x and s.y+1 == ep.y and b.getPiece(s.x-1, s.y) == blackPawn){
                    array.push_back(makeMoves(s, ep, t));
                }
            }
            break;

        case whiteKnight:
            for (int i = 0; i < 8; i++){
                int ix = ((i > 3) + 1) * (((i % 4) > 1) * 2 - 1);
                int iy = (2 - (i > 3)) * ((i % 2 == 0) * 2 - 1);

                piece attackedPiece = b.getPiece(s.x + ix, s.y + iy);

                if (attackedPiece == noPiece and !isWhitePiece(attackedPiece)){
                    Square dest(s.x + ix, s.y + iy);
                    array.push_back(makeMoves(s, dest, t));
                }
            }
            break;

        case whiteBishop:
            break;
        case whiteRook:
            break;
        case whiteQueen:
            break;
        case whiteKing:
            break;       
        default:
            break;
    }
    return array;
}

vector<string> returnMoves(Board b){
    vector<string> moves;
    side t = b.turn;

    for (int x = 0; x < 8; x++){
        for (int y = 0; y < 8; y++){
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
    return moves;
}