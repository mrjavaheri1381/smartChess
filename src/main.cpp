#include <iostream>
#include <Board.h>
using namespace sf;

int main()
{
    std::string board[8][8];
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            std::cin >> board[i][j];
    RenderWindow window(VideoMode(1200, 1200), "Java's Chess", Style::Titlebar | Style::Close);
    Board Chess(board,&window);
    window.setFramerateLimit(20);
    Chess.run();
    return 0;
}