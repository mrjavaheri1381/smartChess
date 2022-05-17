#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;

std::string getPath(std::string piece){
    return "resources/images/Pieces/"+piece+".png";
}

int main()
{
    std::string board[8][8];
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            std::cin >> board[i][j];
    RenderWindow window(VideoMode(1200, 1200), "Java's Chess", Style::Titlebar | Style::Close);
    window.setFramerateLimit(20);
    Texture boardT,pie;
    CircleShape Circle(20);
    Circle.setFillColor(Color(0,255,0));
    boardT.loadFromFile("resources/images/board.png");
    pie.loadFromFile("resources/images/Pieces/BB.png");
    Sprite Back(boardT),piece(pie);
    Back.setScale((float)1200/boardT.getSize().x,(float)1200/boardT.getSize().y);
    piece.setScale((float)200/boardT.getSize().x,(float)200/boardT.getSize().y);
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(Color(150, 150, 150));
        window.draw(Back);
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                if(board[j][i]!="--"){
                    pie.loadFromFile(getPath(board[j][i]));
                    piece.setTexture(pie);
                    if(board[j][i][0]!='P')
                        piece.setPosition(80+i*135,80+j*135);
                    else
                        piece.setPosition(95+i*135,80+j*135);
                    window.draw(piece);
                }
            }
        }
        window.display();
    }
    
    return 0;
}