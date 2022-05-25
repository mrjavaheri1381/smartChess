#include <iostream>
#include <Board.h>
using namespace sf;

int main()
{
    std::string board[8][8];
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            std::cin >> board[i][j];
    RenderWindow window(VideoMode(1200, 1330), "Java's Chess", Style::Titlebar | Style::Close);
    window.setFramerateLimit(20);
    while(window.isOpen()){
        Board Chess(board,&window);
        Chess.run();
    }
    return 0;
}