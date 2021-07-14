#ifndef CAPIZERO
#define CAPIZERO

// TODO organize the includes
#include "benchmark.h"

using namespace std;

#define CAPIZERO_VERSION "alpha 0.1.1"

Board board;

bool read(){
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
    else if (cmd == "flip"){
        board.colorflip();
    }
    else if (cmd == "show"){
        board.printBoard();
    }
    else if (cmd == "fen"){
        cout<<board.fen()<<endl;
    }
    else if (cmd == "exit"){
        return false;
    }
    else if (cmd == "perft"){
        calc_perft(board);
    }
    else if (cmd == "benchmark"){
        bench();
    }
    else if (cmd == "reset"){
        board.setPosition(INITIAL_POSITION);
    }
    else if (cmd == "setposition"){
        string f1;
        string f2;
        string f3;
        string f4;
        string f5;
        string f6;

        cin>>f1;
        cin>>f2;
        cin>>f3;
        cin>>f4;
        cin>>f5;
        cin>>f6;
        
        board.setPosition(f1+" "+f2+" "+f3+" "+f4+" "+f5+" "+f6);

        cout<<"fen sucessfully set to "<<f1+" "+f2+" "+f3+" "+f4+" "+f5+" "+f6<<endl;
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

    return true;
}

#endif