#pragma once
#include "data.h"
#include "Helper.h"
using namespace std;
class BasePies{
    public:
        char pieType;
        int number,color;
        string name;
        Pos pos;
        BasePies(int x=-1 , int y=-1 ,int color=0 ,char type='-');
        bool isClearHorizontal(string[8][8] ,Pos );
        bool isClearVertical(string[8][8] ,Pos );
        bool isClearDiagonal(string[8][8] ,Pos );
        vector<Move> getDiagonalMoves(string[8][8] );
        vector<Move> getVerticalMoves(string[8][8] );
        vector<Move> getHorizontalMoves(string[8][8] );
        virtual bool isValidMove(string[8][8] ,Pos );
        virtual vector<Move> getMoves(string[8][8] );
};