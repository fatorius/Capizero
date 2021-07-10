#include "generate.h"

#include <iostream>
using namespace std;

typedef unsigned long long u64;

u64 perft(int depth, Board pos, bool first = true){
    u64 nodes = 0;
    vector<string> moves = returnMoves(pos);

    if (depth == 0){
        return 1ULL;
    }

    for (int i = 0; i < moves.size(); i++){
        string backUpFen = pos.fen();
        pos.makeMove(moves[i]);
        if (!isCheck(pos)){
            u64 n = perft(depth-1, pos, false);
            if (first){
                cout<<moves[i]<<" -> "<<n<<endl;
            }
            nodes += n;
        }
        pos.setPosition(backUpFen);
    }
    if (first){
        cout<<"\nTotal nodes: ";
    }

    return nodes;
}

bool calc_perft(){
    cout<<"depth: ";
    int depth;
    cin>>depth;

    Board pos;
    cout<<perft(depth, pos)<<endl<<endl;

    return depth;
}

int main(){
    cout<<"capizero 210709"<<endl;
    cout<<"by hugosouza"<<"\n\n";

    while (calc_perft()){}

    return 0;
}