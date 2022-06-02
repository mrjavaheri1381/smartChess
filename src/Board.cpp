#include "Board.h"
using namespace std;
using namespace sf;

std::map<std::string, sf::Texture> textures;

Board::Board(const string brd[8][8],sf::RenderWindow *_window){
  window=_window;
  pieCount[0]=pieCount[1]=0;

  for(int i=0;i<8;i++)
    for(int j=0;j<8;j++){
      string temp=brd[i][j];
      temp.resize(2);
      board[i][j]=temp;
    }
  char temp[2],color='W';
  BasePies *tempPie=new BasePies();
  for(int i=0;i<8;i++)
    for(int j=0;j<8;j++){
      temp[0]=board[i][j][0];
      temp[1]=board[i][j][1];
      if(temp[1]=='W')color=0;
      else if(temp[1]=='B')color=1;
      else color=-1;
      if(temp[0]=='K')
        tempPie=new King(i,j,color);
      else if(temp[0]=='Q')
        tempPie=new Queen(i,j,color);
      else if(temp[0]=='P')
        tempPie=new Pawn(i,j,color);
      else if(temp[0]=='B')
        tempPie=new Bishop(i,j,color);
      else if(temp[0]=='R')
        tempPie=new Rook(i,j,color);
      else if(temp[0]=='N')
        tempPie=new Knight(i,j,color);
      tempPie->name=temp;
        addPie(tempPie);
        tempPie=new BasePies();
    }
}

bool Board::dMode(Move move,int color,int step){
    if(isCheckmate(color))return true;
    bool res=true;
    switch (step){
    case 1:
      MovePie(selectedPiece,move.to);
      res=dMode(move,color,2);
      Undo();
      return res;
    case 2:
        res=false;
        for(int i=0;i<pieCount[!color];i++){
            vector<Move> moves=getValidMoves(Pies[!color][i]);
            for(int j=0;j<moves.size();j++){
                MovePie(Pies[!color][i],moves[j].to);
                if(dMode(move,color,3)){
                Undo();
                return true;
                }
                Undo();
            }
        }
    case 3:
        res=true;
        for(int i=0;i<pieCount[color];i++){
            vector<Move> moves=getValidMoves(Pies[color][i]);
            for(int j=0;j<moves.size();j++){
                MovePie(Pies[color][i],moves[j].to);
                if(!dMode(move,color,4)){
                    Undo();
                    return false;
                }
                Undo();
            }
        }
    case 4:
        res=false;
        for(int i=0;i<pieCount[!color];i++){
            vector<Move> moves=getValidMoves(Pies[!color][i]);
            for(int j=0;j<moves.size();j++){
                MovePie(Pies[!color][i],moves[j].to);
                if(isCheckmate(color)){
                    Undo();
                    return true;
                }
                Undo();
            }
        }
    }
    return res;
}

bool Board::mMode(Move move,int color,int step){
    if(isCheckmate(!color))return true;
    bool res=true;
    switch (step){
    case 1:
      MovePie(selectedPiece,move.to);
      res=mMode(move,color,2);
      Undo();
      return res;   
    case 2:
        res=true;
        for(int i=0;i<pieCount[!color];i++){
            vector<Move> moves=getValidMoves(Pies[!color][i]);
            for(int j=0;j<moves.size();j++){
                MovePie(Pies[!color][i],moves[j].to);
                if(!mMode(move,color,3)){
                Undo();
                return false;
                }
                Undo();
            }
        }
    case 3:
        res=false;
        for(int i=0;i<pieCount[color];i++){
            vector<Move> moves=getValidMoves(Pies[color][i]);
            for(int j=0;j<moves.size();j++){
                MovePie(Pies[color][i],moves[j].to);
                if(isCheckmate(!color)){
                    Undo();
                    return true;
                }
                Undo();
            }
        }
    }
    return res;
}

void Board::addPie(BasePies *pie){
  if(pie->color!=-1){
    pie->number=pieCount[pie->color];
    Pies[pie->color][pieCount[pie->color]]=pie;
    pieCount[pie->color]++;
  }
}

bool Board::isValidMove(BasePies *piece,Move move){
  MovePie(piece,move.to);
  bool flag=isInCheck(piece->color);
  Undo();
  return !flag;
}

void Board::MovePie(BasePies *piece,Pos target,char type){
  if(target.x!=-1&&board[target.x][target.y]!="--"){
    int color=board[target.x][target.y][1]=='W'?0:1;
    BasePies *pie=Pies[color][getByPos(target.x,target.y,board[target.x][target.y][1])];
    Pos tr={-1,-1};
    MovePie(pie,tr);
  }
  Move move={piece->pos,target};
  Action action={move,piece->color,piece->number};
  if(type!='B')Actions.push_back(action);
  if(piece->pos.x!=-1)board[piece->pos.x][piece->pos.y]="--";
  piece->animated=piece->pos;
  piece->pos=target;
  if(target.x!=-1)board[target.x][target.y]=piece->name;
}

void Board::Undo(){
  if(Actions.size()==0) return;
  Action action=Actions.back();
  MovePie(Pies[action.color][action.number],action.move.from,'B');
  Actions.pop_back();
  if(Actions.size()==0) return;
  if(Actions.back().move.to.x==-1) Undo();
}

void Board::changeTurn(){
  turn=turn=='W'?'B':'W';
}

BasePies* Board::getKing(int color){
  for(int i=0;i<pieCount[color];i++)
    if(Pies[color][i]->pieType=='K') return Pies[color][i];
  return new BasePies();
}

int Board::getByPos(int x,int y,char color){
  int cl=color=='W'?0:1;
  for(int i=0;i<pieCount[cl];i++)
    if((Pies[cl][i]->pos.x==x&&Pies[cl][i]->pos.y==y)) return i;
  return 0;
}

vector<Move> Board::getValidMoves(BasePies *piece){
    if(piece->pos.x==-1){
        vector<Move> res;
        return res;
    }
  vector<Move> temp=piece->getMoves(board),res;
  for(int i=0;i<temp.size();i++)
    if(isValidMove(piece,temp[i])) res.push_back(temp[i]);
  return res;
}

bool Board::isInCheck(int color){
  BasePies *King=getKing(color);
  for(int i=0;i<pieCount[!color];i++){
    if(Pies[!color][i]->pos.x!=-1&&Pies[!color][i]->isValidMove(board,King->pos)) return true;
  }
  return false;
}

bool Board::isCheckmate(int color){
  if(!isInCheck(color))return false;
  for(int i=0;i<pieCount[color];i++)
    if(getValidMoves(Pies[color][i]).size()!=0)return false;
  return true;
}

Pos Board::getIndex(int x,int y){
  int i=(y-65)/135,j=(x-65)/135;
  Pos res={i,j};
  return res;
}

bool Board::isInMoves(Pos target){
  for(int i=0;i<avMoves.size();i++)
    if(avMoves[i].to.x==target.x&&avMoves[i].to.y==target.y) return true;
  return false;
}

void Board::touchHandle(int x,int y){
  if(isPlaying)
  for(int i=0;i<2;i++){
    if(isCheckmate(i)){
      isPlaying=false;
      string temp=i==0?"Black":"White";
      winner.setString(temp+" Win!");
      return;
    }
  }
  if(x>1200){
    if(y>30&&y<130&&Actions.size()>0){
      Undo();
      changeTurn();
      selectedPiece=0;
      avMoves.clear();
      isPlaying=true;
      return;
    }
    if(y>1085&&y<1175){
      restart=true;
      return;
    }
  }
  if(!isPlaying)return;
  if(x<1140&&x>65&&y<1140&&y>65){
    Pos index = getIndex(y,x);
    string temp=board[index.x][index.y];
    if(isInMoves(index)){
      MovePie(selectedPiece,index);
      selectedPiece=0;
      avMoves.clear();
      changeTurn();
      return;
    }
    if(temp[1]!=turn||(selectedPiece&&selectedPiece->pos.x==index.x&&selectedPiece->pos.y==index.y)){
      selectedPiece=0;
      avMoves.clear();
    }
    else {
      int color=temp[1]=='W'?0:1;
      int i=getByPos(index.x,index.y,temp[1]);
      selectedPiece=Pies[color][i];
      avMoves=getValidMoves(selectedPiece);
    }
  }
}

void Board::draw(){
  sf::Sprite piece;
  piece.setTexture(textures["KW"]);
  piece.setScale(0,0);
  window->draw(piece);
  if(selectedPiece!=0){
    RectangleShape rectangle(Vector2f(135, 135));
    rectangle.setFillColor(Color(173,181,189));
    rectangle.setPosition(63+selectedPiece->pos.y*135,62+selectedPiece->pos.x*135);
    window->draw(rectangle);
  }
  for(int i=0;i<avMoves.size();i++){
    CircleShape circle(20);
    circle.setFillColor(Color(108,117,125));
    circle.setPosition(110+avMoves[i].to.y*135,110+avMoves[i].to.x*135);
    window->draw(circle);
    if(dMode(avMoves[i],turn=='W'?0:1)){
      Sprite emerg(textures["dMode"]);
      emerg.setPosition(70+avMoves[i].to.y*135,70+avMoves[i].to.x*135);
      emerg.setScale(0.5,0.5);
      window->draw(emerg);
    }
    if(mMode(avMoves[i],turn=='W'?0:1)){
      Sprite emerg(textures["mMode"]);
      emerg.setPosition(70+avMoves[i].to.y*135,70+avMoves[i].to.x*135);
      emerg.setScale(0.5,0.5);
      window->draw(emerg);
    }
  }
  for(int i=0;i<2;i++){
      for(int j=0;j<pieCount[i];j++){
        if(Pies[i][j]->pos.x==-1)continue;
        string key=Pies[i][j]->name;
        key.resize(2);
        piece.setTexture(textures[key]);
        if(selectedPiece&&isInMoves(Pies[i][j]->pos)||(Pies[i][j]->name[0]=='K'&&isInCheck(i)))
          piece.setColor(Color::Red);
        else piece.setColor(Color::White);
        piece.setScale(0.25,0.25);
        if(key[0]!='P'){
            piece.setPosition(80+Pies[i][j]->pos.y*135,80+Pies[i][j]->pos.x*135);
        }
        else{
            piece.setPosition(95+Pies[i][j]->pos.y*135,80+Pies[i][j]->pos.x*135);
        }
        window->draw(piece);
      }
    }
    CircleShape trn(50);
    trn.setPosition(550,1215);
    trn.setFillColor(turn=='W'?Color::White:Color::Black);
    window->draw(trn);
    Sprite undo(textures["undo"]);
    Sprite restart(textures["restart"]);
    undo.setPosition(30,1210);
    undo.setScale(0.8,0.8);
    restart.setPosition(1080,1210);
    restart.setScale(0.8,0.8);
    if(Actions.size()>0)
      window->draw(undo);
    window->draw(restart);
    if(!isPlaying){
      Sprite win(textures["win"]);
      win.setPosition(350,300);
      window->draw(win);
      window->draw(winner);
    }
}
void Board::loadTextures(){
  textures["dMode"].loadFromFile("resources/images/warning.png");
  textures["mMode"].loadFromFile("resources/images/badge.png");
  textures["undo"].loadFromFile("resources/images/undo.png");
  textures["restart"].loadFromFile("resources/images/restart.png");
  textures["win"].loadFromFile("resources/images/win.png");
  for(int i=0;i<2;i++)
    for(int j=0;j<pieCount[i];j++){
      string key=Pies[i][j]->name;
      key.resize(2);
      textures[key].loadFromFile(getPath(key));
    }
}

void Board::run(){
    loadTextures();
    font.loadFromFile("resources/fonts/roboto.ttf");
    winner.setFont(font);
    winner.setCharacterSize(100);
    winner.setStyle(sf::Text::Regular);
    winner.setFillColor(sf::Color::Black);
    winner.setPosition(400, 800);
    selectedPiece=0;
    sf::Sprite sp;
    sf::Texture tx;
    tx.loadFromFile("resources/images/board.png");
    sp.setTexture(tx);
    sp.setScale(1.6,1.6);
    while (this->window->isOpen()&&!restart) {
        sf::Event event;
        while (this->window->pollEvent(event)) {
            if (event.type == Event::Closed) {
                window->close();
            }
            bool lock_click;
            if (event.type == sf::Event::MouseButtonPressed)
                if (event.mouseButton.button == sf::Mouse::Left && lock_click != true){
                    touchHandle(Mouse::getPosition(*(this->window)).y,Mouse::getPosition(*(this->window)).x);
                    lock_click = true; 
                }   
            if (event.type == sf::Event::MouseButtonReleased)
                if (event.mouseButton.button == sf::Mouse::Left) 
                    lock_click = false;
      }
        window->clear(Color(202,174,152));
        window->draw(sp);
        draw();
        this->window->display();
    }
}