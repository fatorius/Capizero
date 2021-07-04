#include "board.h"

#include <ctype.h>
#include <string>
#include <iostream>
using namespace std;


Board::Board(string fen){
    currentPosition = fen;

    setPosition(currentPosition);
}

void Board::setPosition(string newFen){
    square currentSquare = 56;
    int endPosition;
    for (int pos = 0; pos < newFen.size(); pos++){
        char letter = newFen[pos];

        switch (letter){
            case 'r':
                blackRooks[currentSquare] = 1;
                break;
            case 'n':
                blackKnights[currentSquare] = 1;
                break;
            case 'b':
                blackBishops[currentSquare] = 1;
                break;
            case 'q':
                blackQueens[currentSquare] = 1;
                break;
            case 'k':
                blackKings[currentSquare] = 1;
                break;
            case 'p':
                blackPawns[currentSquare] = 1;
                break;
            case 'R':
                whiteRooks[currentSquare] = 1;
                break;
            case 'N':
                whiteKnights[currentSquare] = 1;
                break;
            case 'B':
                whiteBishops[currentSquare] = 1;
                break;
            case 'Q':
                whiteQueens[currentSquare] = 1;
                break;
            case 'K':
                whiteKings[currentSquare] = 1;
                break;
            case 'P':
                whitePawns[currentSquare] = 1;
                break;
            case '/':
                currentSquare -= 15;
                break;
            case '2':
                currentSquare += 1;
                break;
            case '3':
                currentSquare += 2;
                break;
            case '4':
                currentSquare += 3;
                break;
            case '5':
                currentSquare += 4;
                break;
            case '6':
                currentSquare += 5;
                break;
            case '7':
                currentSquare += 6;
                break;
            case '8':
                currentSquare += 7;
                break;
            case ' ':
                endPosition = pos + 1;
                pos = newFen.size();
                break;
        }
        currentSquare++;
    }

    if (newFen[endPosition] == 'w'){
        side = WHITE;
    }
    else{
        side = BLACK;
    }
    
    endPosition += 2;

    string castlings = newFen.substr(endPosition, 4);

    setCastlingSides(newFen.substr(endPosition, 4));

    while (true){
        endPosition++;
        if (isdigit(newFen[endPosition])){
            break;
        }
    }
}

void Board::printBoard(){
    for (int x = 0; x < 8; x++){
        for (int y = 0; y < 8; y++){
            cout<<" "<<pieceToString(getPiece(y, x))<<" ";
        }
        cout<<endl;
    }
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
    return noPiece;
}

square Board::coordinateToSquare(coordinate x, coordinate y){
    return (y * NUMBER_OF_RANKS) + x;
}

void Board::setCastlingSides(string fen){
    if (fen.find("K") != string::npos){
        castlingSides[0] = 1;
    }
    if (fen.find("Q") != string::npos){
        castlingSides[1] = 1;
    }
    if (fen.find("k") != string::npos){
        castlingSides[2] = 1;
    }
    if (fen.find("q") != string::npos){
        castlingSides[3] = 1;
    }   
}

void Board::setMoveAmount(string fen){
    string delimiter = " ";
    size_t pos = fen.find(delimiter);
    string token;

    halfmoves = stoi(fen.substr(0, pos));

    fen.erase(0, pos + delimiter.size());

    fullmoves = stoi(fen);
}

string Board::pieceToString(piece p){
    if (p == whitePawn){
        return "P";
    }
    else if (p == blackPawn){
        return "p";
    }
    else if (p == whiteKnight){
        return "N";
    }
    else if (p == blackKnight){
        return "n";
    }
    else if (p == whiteBishop){
        return "B";
    }
    else if (p == blackBishop){
        return "b";
    }
    else if (p == whiteRook){
        return "R";
    }
    else if (p == blackRook){
        return "r";
    }
    else if (p == whiteQueen){
        return "Q";
    }
    else if (p == blackQueen){
        return "q";
    }
    else if (p == whiteKing){
        return "K";
    }
    else if (p == blackKing){
        return "k";
    }
    else{
        return ".";
    }
}