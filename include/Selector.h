#pragma once
#include <iostream>
#include <Helper.h>
#include <data.h>
#include <SFML/Graphics.hpp>


using namespace std;
class Selector
{
private:
  string **board;
  sf::RenderWindow *window;
  string pen="--";
public:
  Selector(sf::RenderWindow *window);
  void run(string board[8][8]);
  void render(string board[8][8]);
  void touchHandle(int x,int y,string board[8][8]);
  void loadTextures();
  Pos getIndex(int x,int y);

};
