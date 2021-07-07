#include <iostream>

#include "capizero.h"

using namespace std;

int main(){
    vector<string> m = returnMoves(board);
    for (unsigned int i = 0; i < m.size(); i++){
        cout<<m[i]<<endl;
    }
    return 0;
}