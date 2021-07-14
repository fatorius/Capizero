#include "search.h"

#include "eval.h"
#include "generate.h"
#include "attacks.h"

#include <string>
#include <iostream>
using namespace std;

float minimax(Board b, int depth, float alpha, float beta, bool isWhite){

}

string search(Board b, int depth){
    vector<string> moves = returnMoves(b);

    bool isWhite = false;
    float bestEval = -9999;

    if (b.turn == WHITE){
        isWhite = true;
        bestEval = 9999;
    }

    string bestMoveFound;

    int totalMoves = 0;

    string backUpFen = b.fen();

    bool startsInCheck = false;

    if (isWhite){
        b.colorflip();
    }

    startsInCheck = isCheck(b);
    cout<<startsInCheck;

    if (isWhite){
        b.colorflip();
    }
    
    for (unsigned int i = 0; i < moves.size(); i++){
        b.makeMove(moves[i]);

        if (b.turn == WHITE){
            b.colorflip();
        }

        bool isInCheck = isCheck(b);

        if (b.turn == WHITE){
            b.colorflip();
        }

        if (!isInCheck){
            totalMoves++;

            // minimax here
        }

        b.setPosition(backUpFen);
    
    }

    if (totalMoves == 0){
        if (startsInCheck){
            return "checkmate";
        }
        else{
            return "stalemate";
        }
    }

}