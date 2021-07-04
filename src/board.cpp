#include "board.h"

#include <ctype.h>
#include <string>
#include <iostream>
using namespace std;

Square::Square(coordinate c1, coordinate c2){
    x = c1;
    y = c2;
}

square Square::convert(){
    return (y * NUMBER_OF_RANKS) + x;
}

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
                currentSquare -= 17;
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
    for (int x = 7; x >= 0; x--){
        for (int y = 0; y < 8; y++){
            cout<<" "<<pieceToString(getPiece(y, x))<<" ";
        }
        cout<<endl;
    }
}

void Board::makeMove(moves san){
    // e2e4
    piece promotedPiece;
    piece movedPiece;
    string originalSquare = san.substr(0, 2);
    string destinationSquare = san.substr(2, 2);

    //checks if there's a promotion
    if (!isdigit(san[san.size() - 1])){
        promotedPiece = getPromotedPiece(san[san.size() - 1]);
    }

    Square original(getFile(originalSquare), getRank(originalSquare));
    Square destination(getFile(destinationSquare), getRank(destinationSquare));

    movedPiece = getPiece(original.x, original. y);

    setPiece(original, noPiece);
    setPiece(destination, movedPiece);
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

void Board::setPiece(Square s, piece target){
    switch (target){
        case whitePawn:
            whitePawns[s.convert()] = 1;
            break;
        case blackPawn:
            blackPawns[s.convert()] = 1;
            break;
        case whiteKnight:
            whiteKnights[s.convert()] = 1;
            break;
        case blackKnight:
            blackKnights[s.convert()] = 1;
            break;
        case whiteBishop:
            whiteBishops[s.convert()] = 1;
            break;
        case blackBishop:
            blackBishops[s.convert()] = 1;
            break;
        case whiteRook:
            whiteRooks[s.convert()] = 1;
            break;
        case blackRook:
            blackRooks[s.convert()] = 1;
            break;
        case whiteQueen:
            whiteQueens[s.convert()] = 1;
            break;
        case blackQueen:
            blackQueens[s.convert()] = 1;
            break;
        case whiteKing:
            whiteKings[s.convert()] = 1;
            break;
        case blackKing:
            blackKings[s.convert()] = 1;
            break;
        case noPiece:
            whitePawns[s.convert()] = 0;
            blackPawns[s.convert()] = 0;
            whiteKnights[s.convert()] = 0;
            blackKnights[s.convert()] = 0;
            whiteBishops[s.convert()] = 0;
            blackBishops[s.convert()] = 0;
            whiteRooks[s.convert()] = 0;
            blackRooks[s.convert()] = 0;
            whiteQueens[s.convert()] = 0;
            blackQueens[s.convert()] = 0;
            whiteKings[s.convert()] = 0;
            blackKings[s.convert()] = 0;
            break;
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

piece Board::getPromotedPiece(char p){

    piece promotedPiece;

    switch(p){
        case 'N':
            promotedPiece = whiteKnight;
            break;
        case 'n':
            promotedPiece = blackKnight;
            break;
        case 'B':
            promotedPiece = whiteBishop;
            break;
        case 'b':
            promotedPiece = blackBishop;
            break;
        case 'R':
            promotedPiece = whiteRook;
            break;
        case 'r':   
            promotedPiece = blackRook;
            break;
        case 'Q':
            promotedPiece = whiteQueen;
            break;
        case 'q':
            promotedPiece = blackQueen;
            break;
    }

    return promotedPiece;
}

coordinate Board::getFile(string s){
    char rank = s[0];
    
    switch (rank){
        case 'a':
            return 0;
        case 'b':
            return 1;
        case 'c':
            return 2;
        case 'd':
            return 3;
        case 'e':
            return 4;
        case 'f':
            return 5;
        case 'g':
            return 6;
        case 'h':
            return 7;
        default:
            return -1;
    }
}

coordinate Board::getRank(string s){
    char rank = s[1];
    
    switch (rank){
        case '1':
            return 0;
        case '2':
            return 1;
        case '3':
            return 2;
        case '4':
            return 3;
        case '5':
            return 4;
        case '6':
            return 5;
        case '7':
            return 6;
        case '8':
            return 7;
        default:
            return -1;
    }
}