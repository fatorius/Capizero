#include "perft.h"

using namespace std;

u64 perft(int depth, Board pos, bool first){
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

void calc_perft(Board b){
    int depth;
    cout<<"\ndepth: ";
    cin>>depth;

    cout<<perft(depth, b, true)<<endl<<endl;
}
