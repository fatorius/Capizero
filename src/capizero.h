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

        bool valid = false;

        vector<string> m = returnMoves(board);
        for (unsigned int i = 0; i < m.size(); i++){
            if (move == m[i]){
                valid = true;
                break;
            }
        }

        if (valid){
            board.makeMove(move);
        }
        else{
            cout<<move<<" isnt a valid move"<<endl;
        }

    }
    else if (cmd == "show"){
        board.printBoard();
    }
    else if (cmd == "help"){
        cout<<"moves -> print all valid moves on the position"<<endl;
        cout<<"move [san] -> make a move on the board"<<endl;
        cout<<"show -> print the board"<<endl;
    }
    else{
        cout<<cmd<<" not a valid command"<<endl;
    }

    cout<<"\n";
}

#endif