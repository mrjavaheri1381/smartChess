#include <iostream>
#include <sstream>
#include <Board.h>

using namespace sf;

int main()
{
    std::string board[8][8];
    istringstream clipBoard(sf::Clipboard::getString());
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            clipBoard >> board[i][j];
    RenderWindow window(VideoMode(1200, 1330), "Java's Chess", Style::Titlebar | Style::Close);
    window.setFramerateLimit(100);
    while(window.isOpen()){
        Board Chess(board,&window);
        Chess.run();
    }
    return 0;
}