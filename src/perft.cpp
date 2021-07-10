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
        u64 n = perft(depth-1, pos, false);
        if (first){
            cout<<moves[i]<<" -> "<<n<<endl;
        }
        nodes += n;
        
        pos.setPosition(backUpFen);
    }
    if (first){
        cout<<"\nTotal nodes: ";
    }

    return nodes;
}

bool calc_perft(){
    string fen;
    cout<<"fen (s to use starting position): ";
    cin>>fen;
    if (fen == "s"){
        fen = INITIAL_POSITION;
    }
    else{
        string f2;
        string f3;
        string f4;
        string f5;
        string f6;
        cin>>f2;
        cin>>f3;
        cin>>f4;
        cin>>f5;
        cin>>f6;
        fen += " "+f2+" "+f3+" "+f4+" "+f5+" "+f6;
    }
    cout<<"depth: ";
    int depth;
    cin>>depth;

    Board pos(fen);
    cout<<perft(depth, pos)<<endl<<endl;

    return depth;
}

int main(){
    cout<<"capizero 210709"<<endl;
    cout<<"by hugosouza"<<"\n\n";

    while (calc_perft()){}

    return 0;
}