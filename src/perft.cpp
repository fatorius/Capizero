#include "perft.h"

#include <iostream>
using namespace std;

u64 perft(int depth, Board pos){
    u64 nodes = 0;
    vector<string> moves = returnMoves(pos);

    if (depth == 0){
        return 1ULL;
    }

    for (int i = 0; i < moves.size(); i++){
        string backUpFen = pos.fen();
        if (!isCheck(pos)){
            nodes += perft(depth-1, pos);
        }
        pos.setPosition(backUpFen);
    }

    return nodes;
}

int main(){
    int depth;
    cin>>depth;

    Board pos;

    cout<<perft(depth, pos);

    return 0;
}