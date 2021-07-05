#include "board.h"

#include <ctype.h>
#include <cstring>
#include <iostream>

#include <chrono>

using namespace std;

coordinate getFile(string s){
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

coordinate getRank(string s){
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

bool isWhitePiece(piece p){
    if (p == whitePawn or p == whiteKnight or p == whiteBishop or p == whiteRook
        or p == whiteQueen or p == whiteKing){
            return true;
    }
    else{
        return false;
    }
}

piece invertColor(piece p){
    if (p == noPiece){
        return noPiece;
    }
    if (isWhitePiece(p)){
        return p+1;
    }
    else{
        return p-1;
    }
}

Square::Square(squareString s){
    x = getFile(s);
    y = getRank(s);
}

Square::Square(coordinate c1, coordinate c2){
    x = c1;
    y = c2;
}

square Square::convert(){
    return (y * NUMBER_OF_RANKS) + x;
}

Board::Board(string fen){
    currentPosition = fen;

    auto start = chrono::high_resolution_clock::now();
    setPosition(currentPosition);
    auto stop = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(stop-start);

    cout<<duration.count();
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
        turn = WHITE;
    }
    else{
        turn = BLACK;
    }
    
    endPosition += 2;

    string castlings = newFen.substr(endPosition, 4);

    setCastlingSides(newFen.substr(endPosition, 4));

    while (true){
        char letter = newFen[endPosition];
        if (letter == ' '){
            break;
        }
        else{
            endPosition++;
        }
    }

    endPosition++;

    setEnPassantSquare(newFen.substr(endPosition, 2));

    while (true){
        endPosition++;
        if (isdigit(newFen[endPosition])){
            setMoveAmount(newFen.substr(endPosition, newFen.length() - endPosition));
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
    piece promotedPiece = noPiece;
    piece movedPiece;
    string originalSquare = san.substr(0, 2);
    string destinationSquare = san.substr(2, 2);

    //checks if there's a promotion
    if (!isdigit(san[san.size() - 1])){
        promotedPiece = getPromotedPiece(san[san.size() - 1]);
    }

    if (promotedPiece != noPiece){
        Square original(getFile(originalSquare), getRank(originalSquare));
        Square destination(getFile(destinationSquare), getRank(destinationSquare));

        setPiece(original, noPiece);
        setPiece(destination, promotedPiece);
    }
    else if (san == "o-o"){
        if (turn == WHITE){
            Square kingSquare("e1");
            Square rookSquare("h1");

            Square kingFinal("g1");
            Square rookFinal("f1");

            setPiece(kingSquare, noPiece);
            setPiece(rookSquare, noPiece);
            setPiece(kingFinal, whiteKing);
            setPiece(rookFinal, whiteRook);
        }
        else{
            Square kingSquare("e8");
            Square rookSquare("h8");

            Square kingFinal("g8");
            Square rookFinal("f8");

            setPiece(kingSquare, noPiece);
            setPiece(rookSquare, noPiece);
            setPiece(kingFinal, blackKing);
            setPiece(rookFinal, blackRook);
        }
    }
    else if (san == "o-o-o"){
        if (turn == WHITE){
            Square kingSquare("e1");
            Square rookSquare("a1");

            Square kingFinal("c1");
            Square rookFinal("d1");

            setPiece(kingSquare, noPiece);
            setPiece(rookSquare, noPiece);
            setPiece(kingFinal, whiteKing);
            setPiece(rookFinal, whiteRook);
        }
        else{
            Square kingSquare("e8");
            Square rookSquare("a8");

            Square kingFinal("c8");
            Square rookFinal("d8");

            setPiece(kingSquare, noPiece);
            setPiece(rookSquare, noPiece);
            setPiece(kingFinal, blackKing);
            setPiece(rookFinal, blackRook);
        }
    }
    else{
        Square original(getFile(originalSquare), getRank(originalSquare));
        Square destination(getFile(destinationSquare), getRank(destinationSquare));

        movedPiece = getPiece(original.x, original. y);

        if (movedPiece == whitePawn or movedPiece == blackPawn){
            setEnPassantSquareFromMove(san);
            Square enPassant(enPassantSquare);
            if (destination.x == enPassant.x and destination.y == enPassant.y){
                if (enPassantSquare[1] == '3'){
                    Square capturedPiece(enPassant.x, enPassant.y + 1);
                    setPiece(capturedPiece, noPiece);
                }
                else{
                    Square capturedPiece(enPassant.x, enPassant.y - 1);
                    setPiece(capturedPiece, noPiece);
                }
            }
        }
        else{
            enPassantSquare = "-";
        }

        setPiece(original, noPiece);
        setPiece(destination, movedPiece);
    }
    
    if (turn == WHITE){
        turn = BLACK;
    }
    else{
        turn = WHITE;
    }
}

void Board::colorflip(){
    for (int y = 0; y < 8; y++){
        for (int x = 0; x < 4; x++){
            piece p1 = invertColor(getPiece(x, y));
            piece p2 = invertColor(getPiece(7-x, y));
            
            Square s1(x, y);
            Square s2(7-x, y);
            setPiece(s2, p1);
            setPiece(s1, p2);
        }
    }
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
    square converted = s.convert();

    whitePawns[converted] = 0;
    blackPawns[converted] = 0;
    whiteKnights[converted] = 0;
    blackKnights[converted] = 0;
    whiteBishops[converted] = 0;
    blackBishops[converted] = 0;
    whiteRooks[converted] = 0;
    blackRooks[converted] = 0;
    whiteQueens[converted] = 0;
    blackQueens[converted] = 0;
    whiteKings[converted] = 0;
    blackKings[converted] = 0;
    
    switch (target){
        case whitePawn:
            whitePawns[converted] = 1;
            break;
        case blackPawn:
            blackPawns[converted] = 1;
            break;
        case whiteKnight:
            whiteKnights[converted] = 1;
            break;
        case blackKnight:
            blackKnights[converted] = 1;
            break;
        case whiteBishop:
            whiteBishops[converted] = 1;
            break;
        case blackBishop:
            blackBishops[converted] = 1;
            break;
        case whiteRook:
            whiteRooks[converted] = 1;
            break;
        case blackRook:
            blackRooks[converted] = 1;
            break;
        case whiteQueen:
            whiteQueens[converted] = 1;
            break;
        case blackQueen:
            blackQueens[converted] = 1;
            break;
        case whiteKing:
            whiteKings[converted] = 1;
            break;
        case blackKing:
            blackKings[converted] = 1;
            break;
    }
}

void Board::setEnPassantSquare(string fen){
    if (fen == "a3"){
        enPassantSquare = "a3";
    }
    else if (fen == "b3"){
        enPassantSquare = "b3";
    }
    else if (fen == "c3"){
        enPassantSquare = "c3";
    }
    else if (fen == "d3"){
        enPassantSquare = "d3";
    }
    else if (fen == "e3"){
        enPassantSquare = "e3";
    }
    else if (fen == "f3"){
        enPassantSquare = "f3";
    }
    else if (fen == "g3"){
        enPassantSquare = "g3";     
    }
    else if (fen == "h3"){
        enPassantSquare = "h3";
    }
    else if (fen == "a6"){
        enPassantSquare = "a6";
    }
    else if (fen == "b6"){
        enPassantSquare = "c6";
    }
    else if (fen == "c6"){
        enPassantSquare = "c6"; 
    }
    else if (fen == "d6"){
        enPassantSquare = "d6";  
    }
    else if (fen == "e6"){
        enPassantSquare = "e6";
    }
    else if (fen == "f6"){
        enPassantSquare = "f6";
    }
    else if (fen == "g6"){
        enPassantSquare = "g6";
    }
    else if (fen == "h6"){
        enPassantSquare = "h6";  
    }
    else{
        enPassantSquare = "-";
    }
}

void Board::setEnPassantSquareFromMove(string fen){
    if (fen == "a2a4"){
        enPassantSquare = "a3";
    }
    else if (fen == "b2b4"){
        enPassantSquare = "b3";
    }
    else if (fen == "c2c4"){
        enPassantSquare = "c3";
    }
    else if (fen == "d2d4"){
        enPassantSquare = "d3";
    }
    else if (fen == "e2e4"){
        enPassantSquare = "e3";
    }
    else if (fen == "f2f4"){
        enPassantSquare = "f3";
    }
    else if (fen == "g2g4"){
        enPassantSquare = "g3";     
    }
    else if (fen == "h2h4"){
        enPassantSquare = "h3";
    }
    else if (fen == "a7a5"){
        enPassantSquare = "a6";
    }
    else if (fen == "b7b5"){
        enPassantSquare = "c6";
    }
    else if (fen == "c7c5"){
        enPassantSquare = "c6"; 
    }
    else if (fen == "d7d5"){
        enPassantSquare = "d6";  
    }
    else if (fen == "e7e5"){
        enPassantSquare = "e6";
    }
    else if (fen == "f7f5"){
        enPassantSquare = "f6";
    }
    else if (fen == "g7g5"){
        enPassantSquare = "g6";
    }
    else if (fen == "h7h5"){
        enPassantSquare = "h6";  
    }
    else{
        enPassantSquare = "-";
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
