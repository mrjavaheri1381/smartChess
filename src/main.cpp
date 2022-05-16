#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
  
int main()
{
    RenderWindow window(VideoMode(1200, 1200), "Java's Chess", Style::Titlebar | Style::Close);
    window.setFramerateLimit(20);
    Texture boardT;
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
        }
        window.clear(Color(150, 150, 150));
        window.draw(Back);
        window.display();
    }
    
    return 0;
}