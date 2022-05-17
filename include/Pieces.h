#pragma once
#include "basePiece.h"
#include <vector>

using namespace std;
class King : public BasePies {
    public:
        King(int x=-1, int y=-1, char color='b');
        vector<Move> getMoves(string board[8][8]);
        bool isValidMove(string board[8][8],Pos target);
};
class Bishop : public BasePies {
    public:
        Bishop(int x=-1, int y=-1, char color='b');
        vector<Move> getMoves(string board[8][8]);
        bool isValidMove(string board[8][8],Pos target);
};
class Knight : public BasePies {
    public:
        Knight(int x=-1, int y=-1, char color='b');
        vector<Move> getMoves(string board[8][8]);
        bool isValidMove(string board[8][8],Pos target);
};
class Queen : public BasePies {
    public:
        Queen(int x=-1, int y=-1, char color='b');
        vector<Move> getMoves(string board[8][8]);
        bool isValidMove(string board[8][8],Pos target);
};
class Pawn : public BasePies {
    public:
        Pawn(int x=-1, int y=-1, char color='b');
        vector<Move> getMoves(string board[8][8]);
        bool isValidMove(string board[8][8],Pos target);
};
class Rook : public BasePies {
    public:
        Rook(int x=-1, int y=-1, char color='b');
        vector<Move> getMoves(string board[8][8]);
        bool isValidMove(string board[8][8],Pos target);
};

