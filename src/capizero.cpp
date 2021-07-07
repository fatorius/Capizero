#include <iostream>

#include "capizero.h"

using namespace std;

int main(){
    board.makeMove("e2e4");
    board.makeMove("e7e5");
    board.makeMove("g1f3");
    board.makeMove("b8c6");
    board.makeMove("f1b5");
    board.makeMove("g8f6");
    
    vector<string> m = returnMoves(board);
    for (unsigned int i = 0; i < m.size(); i++){
        cout<<m[i]<<endl;
    }
    return 0;
}