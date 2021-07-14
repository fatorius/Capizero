#include "benchmark.h"

#include "perft.h"
#include "search.h"
#include "board.h"

using namespace std;

void bench(){
    Board b;

    auto start = chrono::high_resolution_clock::now();
    perft(3, b, false);
    auto end = chrono::high_resolution_clock::now();

    double time = chrono::duration_cast<chrono::nanoseconds>(end-start).count();

    time *= 1e-9;

    cout<<"Perft at depth 3 took ";

    cout<<time<<setprecision(9)<<" secs"<<endl<<endl;
}
