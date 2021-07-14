#include "perft.h"

#include "generate.h"
#include "attacks.h"

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
        
        if (pos.turn == WHITE){
            pos.colorflip();
        }

        bool isInCheck = isCheck(pos);
        
        if (pos.turn == WHITE){
            pos.colorflip();
        }
        
        if (!isInCheck){  
            u64 n = perft(depth-1, pos, false);
            if (first){
                cout<<moves[i]<<" -> "<<n<<endl;
            }
            nodes += n;
        }
        
        pos.setPosition(backUpFen);
    }
    if (first){
        cout<<"\n"<<nodes<<" nodes calculated in ";
    }

    return nodes;
}

void calc_perft(Board b){
    int depth;
    cout<<"\ndepth: ";
    cin>>depth;

    auto start = chrono::high_resolution_clock::now();
    perft(depth, b, true);
    auto end = chrono::high_resolution_clock::now();

    double time = chrono::duration_cast<chrono::nanoseconds>(end-start).count();

    time *= 1e-9;

    cout<<time<<setprecision(9)<<" secs"<<endl<<endl;
}
