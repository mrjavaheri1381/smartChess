#pragma once
#include "Pieces.h"
#include <SFML/Graphics.hpp>
using namespace std;
class Board
{
  public:
    int pieCount[2];
    string board[8][8];
    BasePies *Pies[2][16];
    vector<Action> Actions;
    Board(string brd[8][8]);
    bool dMode(int color,int step=1);
    bool mMode(int color,int step=1);
    void addPie(BasePies *pie);
    string convertPos(Pos pos);
    string convertMove(BasePies *pie,Move move);
    bool isValidMove(BasePies *piece,Move move);
    void MovePie(BasePies *piece,Pos target,char type='N');
    void Undo();
    BasePies* getKing(int color);
    int getByPos(int x,int y);
    vector<Move> getValidMoves(BasePies *piece);
    bool isInCheck(int color);
    bool isCheckmate(int color);
};
