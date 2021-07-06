#include <iostream>

#include "capizero.h"

using namespace std;

int main(){
    board.makeMove("e2e4");
    board.makeMove("g8h6");
    board.makeMove("e4e5");
    board.makeMove("f7f5");
    vector<string> m = returnMoves(board);
    for (unsigned int i = 0; i < m.size(); i++){
        cout<<m[i]<<endl;
    }
    return 0;
}