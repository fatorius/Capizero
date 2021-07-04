#include "board.h"

#include <iostream>
using namespace std;


Board::Board(string fen){
    currentPosition = fen;

    setPosition(currentPosition);
}

void Board::setPosition(string newFen){
    cout<<"a"; 
}

piece Board::getPiece(coordinate x, coordinate y){
    square s = coordinateToSquare(x, y);

    if (whitePawns[s]){
        return whitePawn;
    }
    else if (blackPawns[s]){
        return blackPawn;
    }
    else if (whiteKnights[s]){
        return whiteKnight;
    }
    else if (blackKnights[s]){
        return blackKnight;
    }
    else if (whiteBishops[s]){
        return whiteBishop;
    }
    else if (blackBishops[s]){
        return blackBishop;
    }
    else if (whiteRooks[s]){
        return whiteRook;
    }
    else if (blackRooks[s]){
        return blackRook;
    }
    else if (whiteQueens[s]){
        return whiteQueen;
    }
    else if (blackQueens[s]){
        return blackQueen;
    }
    else if (whiteKings[s]){
        return whiteKing;
    }
    else if (blackKings[s]){
        return blackKing;
    }
    return NO_PIECE;
}

square Board::coordinateToSquare(coordinate x, coordinate y){
    return (y * NUMBER_OF_RANKS) + (x + 1);
}
