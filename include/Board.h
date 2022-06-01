#pragma once
#include "Pieces.h"
#include "Helper.h"
#include <SFML/Graphics.hpp>
using namespace std;
class Board
{
  public:
    int pieCount[2];
    char turn='W';
    bool isPlaying=true,restart=false;
    string board[8][8];
    sf::RenderWindow *window;
    sf::Font font;
    sf::Text winner;
    BasePies *Pies[2][16];
    BasePies *selectedPiece;
    vector<Action> Actions;
    vector<Move> avMoves;
    Board(const string brd[8][8],sf::RenderWindow *window);
    bool dMode(Move move,int color,int step=1);
    bool mMode(Move move,int color,int step=1);
    void addPie(BasePies *pie);
    bool isValidMove(BasePies *piece,Move move);
    void MovePie(BasePies *piece,Pos target,char type='N');
    void Undo();
    BasePies* getKing(int color);
    int getByPos(int x,int y,char color);
    vector<Move> getValidMoves(BasePies *piece);
    bool isInCheck(int color);
    bool isCheckmate(int color);
    void draw();
    void changeTurn();
    Pos findPos(sf::Vector2f position);
    void touchHandle(int x,int y);
    void init();
    void run();
    bool isInMoves(Pos target);
};