#include <iostream>
#include <Board.h>
using namespace sf;

int main()
{
    std::string board[8][8];
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            std::cin >> board[i][j];
    Board Chess(board);
    RenderWindow window(VideoMode(1200, 1200), "Java's Chess", Style::Titlebar | Style::Close);
    window.setFramerateLimit(20);
    Texture boardT;
    CircleShape Circle(20);
    Circle.setFillColor(Color(0,255,0));
    boardT.loadFromFile("resources/images/board.png");
    Sprite Back(boardT);
    Back.setScale((float)1200/boardT.getSize().x,(float)1200/boardT.getSize().y);
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                Pos pos={3,4};
                // Chess.board[0][0]="KW";
                Chess.MovePie(Chess.Pies[0][10],pos);
            }
        }
        window.clear(Color(150, 150, 150));
        window.draw(Back);
        // Chess.draw(&window);
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                if(1){
                    Texture pie;
                    Sprite piece;
                    cout<<board[i][j]<<' ';
                    // pie.loadFromFile(getPath(Chess.board[j][i]));
                    // piece.setTexture(pie);
                    // piece.setScale(0.2,0.2);
                    // if(Chess.board[j][i][0]!='P')
                    //     piece.setPosition(80+i*135,80+j*135);
                    // else
                    //     piece.setPosition(95+i*135,80+j*135);
                    // window.draw(piece);
                }
                cout<<'\n';
            }
        }
        window.display();
    }
    
    return 0;
}