#ifndef BOARD_H
#define BOARD_H

#include <string>
using namespace std;

class Board{

    public:
        Board(string fen);

        string currentPosition;

};

#endif