#pragma once
#include "Pieces.h"
#include <SFML/Graphics.hpp>
using namespace std;
class Board
{
  public:
    int pieCount[2];
    char turn;
    string board[8][8];
    sf::RenderWindow *window;
    BasePies *Pies[2][16];
    BasePies *selectedPiece;
    vector<Action> Actions;
    vector<Move> avMoves;
    Board(const string brd[8][8],sf::RenderWindow *window);
    bool dMode(int color,int step=1);
    bool mMode(int color,int step=1);
    void addPie(BasePies *pie);
    string convertPos(Pos pos);
    string convertMove(BasePies *pie,Move move);
    bool isValidMove(BasePies *piece,Move move);
    void MovePie(BasePies *piece,Pos target,char type='N');
    void Undo();
    BasePies* getKing(int color);
    int getByPos(int x,int y,char color);
    vector<Move> getValidMoves(BasePies *piece);
    bool isInCheck(int color);
    bool isCheckmate(int color);
    void loadTextures();
    void draw();
    Pos findPos(sf::Vector2f position);
    void touchHandle(sf::Vector2f position);
    void init();
    void run();
};