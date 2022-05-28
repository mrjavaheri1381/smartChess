#include <iostream>
#include <sstream>
#include <Board.h>

using namespace sf;

int main()
{
    std::string board[8][8];
    char type;
    cout<<"Select Input type:\n-A:Clipboard\n-B:In console\n:";
    istringstream clipBoard(sf::Clipboard::getString());
    cin>>type;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++){
            if(type=='A')clipBoard >> board[i][j];
            if(type=='B')cin >> board[i][j];
        }
    RenderWindow window(VideoMode(1200, 1330), "Java's Chess", Style::Titlebar | Style::Close);
    window.setFramerateLimit(100);
    while(window.isOpen()){
        Board Chess(board,&window);
        Chess.run();
    }
    return 0;
}