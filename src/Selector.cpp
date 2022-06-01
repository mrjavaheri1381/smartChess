#include <Selector.h>

Selector::Selector(sf::RenderWindow *_window):window(_window){}

void Selector::loadTextures(){
  textures["undo"].loadFromFile("resources/images/undo.png");
  textures["restart"].loadFromFile("resources/images/restart.png");
  textures["win"].loadFromFile("resources/images/win.png");
  char pies[]={'B','K','N','P','Q','R'};
  char color[]={'W','B'};
  for(int i=0;i<2;i++)
    for(int j=0;j<8;j++){
      string key;
      key.resize(2);
      key[0]=pies[j];
      key[1]=color[i];
      textures[key].loadFromFile(getPath(key));
    }
}

void Selector::run(string board[8][8]){
    while (this->window->isOpen()) {
            sf::Event event;
            while (this->window->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window->close();
                }
                bool lock_click;
                if (event.type == sf::Event::MouseButtonPressed)
                    if (event.mouseButton.button == sf::Mouse::Left && lock_click != true){
                        // touchHandle(Mouse::getPosition(*(this->window)).y,Mouse::getPosition(*(this->window)).x);
                        lock_click = true; 
                    }   
                if (event.type == sf::Event::MouseButtonReleased)
                    if (event.mouseButton.button == sf::Mouse::Left) 
                        lock_click = false;
          }
            window->clear(sf::Color(202,174,152));
            // window->draw(sp);
            // draw();
            this->window->display();
        }
}