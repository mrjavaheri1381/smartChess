#pragma once
#include <iostream>
#include <Helper.h>
#include <Board.h>
#include <SFML/Graphics.hpp>
using namespace std;
class Selector
{
private:
  string **board;
  sf::RenderWindow *window;
public:
  Selector(sf::RenderWindow *window);
  void run(string board[8][8]);
  void loadTextures();
};
