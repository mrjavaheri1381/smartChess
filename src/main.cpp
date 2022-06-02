#include <iostream>
#include <sstream>
#include <Board.h>
#include <Selector.h>

using namespace sf;

int main()
{
    std::string board[8][8];
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            board[i][j]="--";
    char type;
    cout<<"Select Input type:\n-A:Clipboard\n-B:In console\n-C:In editor\n:";
    istringstream clipBoard(sf::Clipboard::getString());
    cin>>type;
    if(type!='C'){
        for(int i=0;i<8;i++)
            for(int j=0;j<8;j++){
                if(type=='A')clipBoard >> board[i][j];
                if(type=='B')cin >> board[i][j];
            }
    }
    else{
        RenderWindow window(VideoMode(1600, 1300), "Editor", Style::Titlebar | Style::Close);
        window.setFramerateLimit(20);
        Selector selector(&window);
        selector.run(board);
    }
    RenderWindow window(VideoMode(1200, 1330), "Java's Chess", Style::Titlebar | Style::Close);
    window.setFramerateLimit(20);
    while(window.isOpen()){
        Board Chess(board,&window);
        Chess.run();
    }
    return 0;
}