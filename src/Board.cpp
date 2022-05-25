#include "Board.h"
using namespace std;
map<string, sf::Texture> textures;

Board::Board(const string brd[8][8],sf::RenderWindow *_window){
  window=_window;
  pieCount[0]=pieCount[1]=0;
  for(int i=0;i<8;i++)
    for(int j=0;j<8;j++)
        board[i][j]=brd[i][j];
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
bool Board::dMode(int color,int step){
    if(isCheckmate(color))return true;
    bool res=true;
    vector<string> result;
    switch (step){
    case 1:
        for(int i=0;i<pieCount[color];i++){
            vector<Move> moves=getValidMoves(Pies[color][i]);
            vector<string> tempres;
            for(int j=0;j<moves.size();j++){
                MovePie(Pies[color][i],moves[j].to);
                if(dMode(color,2))tempres.push_back(convertMove(Pies[color][i],moves[j]));
                Undo();
            }
        if(moves.size()!=0&&tempres.size()==moves.size())result.push_back(convertPos(Pies[color][i]->pos)+Pies[color][i]->name);
        else for(int x=0;x<tempres.size();x++)result.push_back(tempres[x]);
        }
        for(int i=0;i<result.size();i++)
            for(int j=i+1;j<result.size();j++)
                if(result[i]>result[j]){
                    string temp=result[i];
                    result[i]=result[j];
                    result[j]=temp;
                }
        for(int i=0;i<result.size();i++)cout<<result[i]<<'\n';
        if(result.size()==0)cout<<"No Answer!";
    case 2:
        res=false;
        for(int i=0;i<pieCount[!color];i++){
            vector<Move> moves=getValidMoves(Pies[!color][i]);
            for(int j=0;j<moves.size();j++){
                MovePie(Pies[!color][i],moves[j].to);
                if(dMode(color,3)){
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
                if(!dMode(color,4)){
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
bool Board::mMode(int color,int step){
    if(isCheckmate(!color))return true;
    bool res=true;
    vector<string> result;
    switch (step){
    case 1:
        for(int i=0;i<pieCount[color];i++){
            vector<Move> moves=getValidMoves(Pies[color][i]);
            vector<string> tempres;
            for(int j=0;j<moves.size();j++){
                MovePie(Pies[color][i],moves[j].to);
                if(mMode(color,2)){ 
                    tempres.push_back(convertMove(Pies[color][i],moves[j]));
                }
                Undo();
            }
        if(moves.size()!=0&&tempres.size()==moves.size())result.push_back(convertPos(Pies[color][i]->pos)+Pies[color][i]->name);
        else
        for(int x=0;x<tempres.size();x++)result.push_back(tempres[x]);
        }
        for(int i=0;i<result.size();i++)
            for(int j=i+1;j<result.size();j++)
                if(result[i]>result[j]){
                    string temp=result[i];
                    result[i]=result[j];
                    result[j]=temp;
                }
        for(int i=0;i<result.size();i++)cout<<result[i]<<'\n';
        if(result.size()==0)cout<<"No Answer!";
    case 2:
        res=true;
        for(int i=0;i<pieCount[!color];i++){
            vector<Move> moves=getValidMoves(Pies[!color][i]);
            for(int j=0;j<moves.size();j++){
                MovePie(Pies[!color][i],moves[j].to);
                if(!mMode(color,3)){
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
string Board::convertPos(Pos pos){
  string res="a0";
  res[0]=(char)('a'+pos.y);
  res[1]='8'-pos.x;
  return res;
}
string Board::convertMove(BasePies *pie,Move move){
  return convertPos(move.from)+pie->name+convertPos(move.to);
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
void Board::loadTextures(){
  for(int i=0;i<2;i++)
    for(int j=0;j<pieCount[i];j++){
      string key=Pies[i][j]->name;
      key.resize(2);
      textures[key].loadFromFile(getPath(key));
    }
}
using namespace sf;
Pos getIndex(int x,int y){
  int i=(y-65)/135,j=(x-65)/135;
  Pos res={i,j};
  return res;
}
void Board::touchHandle(int x,int y){

  if(x<1140&&x>65&&y<1140&&y>65||1){
    Pos index = getIndex(x,y);
    string temp=board[index.y][index.x];
    temp.resize(2);
    if(temp[1]!=turn){
    selectedPiece=0;
    }
    else{
      int color=temp[1]=='W'?0:1;
      int i=getByPos(index.y,index.x,temp[1]);
      selectedPiece=Pies[color][i];
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
    rectangle.setFillColor(Color(12,222,12));
    rectangle.setPosition(65+selectedPiece->pos.y*135,65+selectedPiece->pos.x*135);
    window->draw(rectangle);
  }
  for(int i=0;i<2;i++){
      for(int j=0;j<pieCount[i];j++){
        string key=Pies[i][j]->name;
        key.resize(2);
        piece.setTexture(textures[key]);
        piece.setScale(0.25,0.25);
        if(key[0]!='P')
            piece.setPosition(80+Pies[i][j]->pos.y*135,80+Pies[i][j]->pos.x*135);
        else
            piece.setPosition(95+Pies[i][j]->pos.y*135,80+Pies[i][j]->pos.x*135);
        window->draw(piece);
      }
    }
}
void Board::run(){
    loadTextures();
    sf::Sprite sp;
    sf::Texture tx;
    tx.loadFromFile("resources/images/board.png");
    sp.setTexture(tx);
    sp.setScale(1.6,1.6);
    while (this->window->isOpen()) {
        sf::Event event;
        while (this->window->pollEvent(event)) {
            if (event.type == Event::Closed) {
                window->close();
            }
            if (Mouse::isButtonPressed(Mouse::Left)) {
                touchHandle(Mouse::getPosition(*(this->window)).y,Mouse::getPosition(*(this->window)).x);
            }
        }
        window->draw(sp);
        draw();
        this->window->display();
    }
}