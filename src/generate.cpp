#include "generate.h"

using namespace std;

moves makeMoves(Square x, Square y){
    return x.getString() + y.getString();
}

vector<string> generate(Board b, Square s, piece p){
    switch (p){
        case whitePawn:
            break;
        case blackPawn:
            break;
        case whiteKnight:
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
}

vector<string> returnMoves(Board b){
    vector<string> moves;

    for (int x = 0; x < 8; x++){
        for (int y = 0; y < 8; y++){
            Square s(x, y);
            piece p = b.getPiece(s);
            if (p == noPiece){
                continue;
            }
            vector<string> tempMoves = generate(b, s, p);
        }
    }

    return moves;
}