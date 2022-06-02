#include <Selector.h>
std::map<std::string, sf::Texture> textures1;

Selector::Selector(sf::RenderWindow *_window):window(_window){}

void Selector::loadTextures(){
  textures1["undo"].loadFromFile("resources/images/undo.png");
  textures1["restart"].loadFromFile("resources/images/restart.png");
  textures1["win"].loadFromFile("resources/images/win.png");
  char pies[]={'B','K','N','P','Q','R'};
  char color[]={'W','B'};
  for(int i=0;i<2;i++)
    for(int j=0;j<6;j++){
      string key;
      key.resize(2);
      key[0]=pies[j];
      key[1]=color[i];
      textures1[key].loadFromFile(getPath(key));
    }
}
using namespace sf;

Pos Selector::getIndex(int x,int y){
  int i=(y-65)/135,j=(x-265)/135;
  Pos res={i,j};
  return res;
}


void Selector::touchHandle(int x,int y,string board[8][8]){
    if(x>265&&x<1350&&y>65&&y<1150){
        Pos index = getIndex(x,y);
        board[index.x][index.y]=pen;
        pen="--";
    }
    if(y<1200&&x<265||x>1350){
        char pies[]={'B','K','N','P','Q','R'};
        string temp;
        temp.resize(2);
        temp[0]=pies[(int)y/200];
        temp[1]=x<265?'W':'B';
        if(temp==pen)pen="--";
        else pen=temp;

    }
    if(y>1225&&y<1286&&x>800&&x<870){
        window->close();
    }

}

void Selector::render(string board[8][8]){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            sf::Sprite sp;
            if(board[i][j]!="--"){
                sp.setTexture(textures1[board[i][j]]);
                if(board[i][j][0]=='P')
                    sp.setPosition(295+j*135,75+i*135);
                else
                    sp.setPosition(280+j*135,75+i*135);
                sp.setScale(0.25,0.25);
                window->draw(sp);
            }
        }
    }
}


void Selector::run(string board[8][8]){
    loadTextures();
    while (this->window->isOpen()) {
            sf::Event event;
            while (this->window->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window->close();
                }
                bool lock_click;
                if (event.type == sf::Event::MouseButtonPressed)
                    if (event.mouseButton.button == sf::Mouse::Left && lock_click != true){
                        touchHandle(Mouse::getPosition(*(this->window)).x,Mouse::getPosition(*(this->window)).y,board);
                        lock_click = true; 
                    }   
                if (event.type == sf::Event::MouseButtonReleased)
                    if (event.mouseButton.button == sf::Mouse::Left) 
                        lock_click = false;
          }
        sf::Sprite sp;
        sf::Texture tx;
        tx.loadFromFile("resources/images/board.png");
        sp.setTexture(tx);
        sp.setPosition(200,0);
        sp.setScale(1.6,1.6);
        window->clear(sf::Color(202,174,152));
        window->draw(sp);
        char pies[]={'B','K','N','P','Q','R'};
        char color[]={'W','B'};
        for(int i=0;i<2;i++){
            for(int j=0;j<6;j++){
            string key;
            key.resize(2);
            key[0]=pies[j];
            key[1]=color[i];
            sf::Sprite sp;
            sp.setScale(0.4,0.4);
            sp.setTexture(textures1[key]);
            if(key[0]=='P')
                sp.setPosition(key[1]=='W'?40:1440,j*200);
            else
                sp.setPosition(key[1]=='W'?20:1420,j*200);
            if(key==pen)
                sp.setColor(Color::Green);
            window->draw(sp);
            }
        }
        sf::Sprite submit;
        tx.loadFromFile("resources/images/confirm.png");
        submit.setTexture(tx);
        submit.setPosition(800,1220);
        window->draw(submit);
        render(board);
        window->display();
}
}