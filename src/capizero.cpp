#include <iostream>

#include "capizero.h"

using namespace std;

int main(){
    board.makeMove("a2a3");
    vector<string> m = returnMoves(board);
    for (unsigned int i = 0; i < m.size(); i++){
        cout<<m[i]<<endl;
    }
    return 0;
}