#ifndef CAPIZERO
#define CAPIZERO

#include "generate.h"

#define CAPIZERO_VERSION "alpha 0.1.1"

Board board;

void read(){
    string cmd;
    cin>>cmd;

    cout<<"\n";

    if (cmd == "moves"){
        vector<string> m = returnMoves(board);
        for (unsigned int i = 0; i < m.size(); i++){
            cout<<m[i]<<endl;
        }
    }
    else if (cmd == "move"){
        string move;
        cin>>move;

        board.makeMove(move);
    }
    else if (cmd == "show"){
        board.printBoard();
    }
    else{
        cout<<cmd<<" not a valid command"<<endl;
    }

    cout<<"\n";
}

#endif