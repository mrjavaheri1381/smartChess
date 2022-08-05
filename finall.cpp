#include <iostream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;
struct Pos {
    int x,y;
};
struct Move{
    Pos from,to;
};
struct Action{
    Move move;
    int color,number;
};
bool isValidPos(int x,int y){
    return x<8&&x>=0&&y>=0&&y<8;
}
class BasePies{
    public:
        char pieType;
        int number,color;
        string name;
        Pos pos;
        BasePies(int x=-1, int y=-1,int color=-1,char type='-') {
            pos.x = x;
            pos.y = y;
            this->pieType = type;
            this->color = color;
        }
        bool isClearHorizontal(string board[8][8],Pos target){
            if(pos.x!=target.x)return false;
            if(pos.y>target.y)
                for(int i=pos.y-1;i>target.y;i--)
                    if(board[pos.x][i][1]!='-')
                        return false;
            if(pos.y<target.y)
                for(int i=pos.y+1;i<target.y;i++)
                    if(board[pos.x][i][1]!='-') 
                        return false;
            return true;
        }
        bool isClearVertical(string board[8][8],Pos target){
            if(pos.y!=target.y)return false;
            if(pos.x>target.x)
                for(int i=pos.x-1;i>target.x;i--)
                    if(board[i][pos.y][1]!='-') return false;
            if(pos.x<target.x)
                for(int i=pos.x+1;i<target.x;i++)
                    if(board[i][pos.y][1]!='-') return false;
            return true;
        }
        bool isClearDiagonal(string board[8][8],Pos target){
            if(abs(pos.x-target.x)!=abs(pos.y-target.y))return false;
            int kx=pos.x>target.x?-1:1,ky=pos.y>target.y?-1:1;
            for(int i=1;;i++){
                if(pos.x+i*kx==target.x&&pos.y+i*ky==target.y)return true;  
                if(board[pos.x+kx*i][pos.y+i*ky][1]!='-') return false;     
            }
            return true;
        }
        vector<Move> getDiagonalMoves(string board[8][8]){
            vector<Move> res;
            for(int i=1;i<8;i++){
                Pos p={pos.x+i,pos.y+i};
                Move temp={pos,p};
                if(pos.x+i==8||pos.y+i==8) break;
                if(board[pos.x+i][pos.y+i][1]=='-') res.push_back(temp);
                else if (board[pos.x+i][pos.y+i][1]==name[1]) break;
                else{
                    res.push_back(temp);
                   break;
                }
            }
            for(int i=1;i<8;i++){
                Pos p={pos.x-i,pos.y+i};
                Move temp={pos,p};
                if(pos.x-i==-1||pos.y+i==8) break; 
                if(board[pos.x-i][pos.y+i][1]=='-') res.push_back(temp);
                else if (board[pos.x-i][pos.y+i][1]==name[1]) break;
                else{
                    res.push_back(temp);
                    break;
                }
            }
            for(int i=1;i<8;i++){
                Pos p={pos.x+i,pos.y-i};
                Move temp={pos,p};
                if(pos.x+i==8||pos.y-i==-1) break;
                if(board[pos.x+i][pos.y-i][1]=='-') res.push_back(temp);
                else if (board[pos.x+i][pos.y-i][1]==name[1]) break;
                else{
                    res.push_back(temp);
                   break;
                }
            }
            for(int i=1;i<8;i++){
                Pos p={pos.x-i,pos.y-i};
                Move temp={pos,p};
                if(pos.x-i==-1||pos.y-i==-1) break;
                if(board[pos.x-i][pos.y-i][1]=='-') res.push_back(temp);
                else if (board[pos.x-i][pos.y-i][1]==name[1]) break;
                else{
                    res.push_back(temp);
                    break;
                }
            }
            return res;
        }
        vector<Move> getVerticalMoves(string board[8][8]){
            vector<Move> res;
            for(int i=pos.x+1;i<8;i++){
                Pos p={i,pos.y};
                Move temp={pos,p};
                if(board[i][pos.y][1]=='-')res.push_back(temp);
                else if(board[i][pos.y][1]==name[1])break;
                else{
                    res.push_back(temp);
                    break;
                }
            }
            for(int i=pos.x-1;i>=0;i--){
                Pos p={i,pos.y};
                Move temp={pos,p};
                if(board[i][pos.y][1]=='-')res.push_back(temp);
                else if(board[i][pos.y][1]==name[1]) break;
                else{
                    res.push_back(temp);
                    break;       
                }
            }
            return res;
        }
        vector<Move> getHorizontalMoves(string board[8][8]){
            vector<Move> res;
            for(int i=pos.y+1;i<8;i++){
                Pos p={pos.x,i};
                Move temp={pos,p};
                if(board[pos.x][i][1]=='-')res.push_back(temp);
                else if(board[pos.x][i][1]==name[1]) break;
                else{
                    res.push_back(temp);
                   break;         
                }
            }
            for(int i=pos.y-1;i>=0;i--){
                Pos p={pos.x,i};
                Move temp={pos,p};
                if(board[pos.x][i][1]=='-')res.push_back(temp);
                else if(board[pos.x][i][1]==name[1]) break;
                else{
                    res.push_back(temp);
                    break;        
                }
            }
            return res;
        }
        virtual bool isValidMove(string board[8][8],Pos target){return true;}
        virtual vector<Move> getMoves(string board[8][8]){
            vector<Move> res;
            return res;
        }

};

class King : public BasePies {
    public:
        King(int x=-1, int y=-1, char color='b') : BasePies(x, y, color) {
            pieType = 'K';
        }
        vector<Move> getMoves(string board[8][8]){
            vector<Move> res;
            char col=color==0?'W':'B';
            int dx[8]={1,1,1,0,0,-1,-1,-1};
            int dy[8]={0,1,-1,-1,1,-1,1,0};
            for(int i=0;i<8;i++)
                if(isValidPos(pos.x+dx[i],pos.y+dy[i])&&board[pos.x+dx[i]][pos.y+dy[i]][1]!=col){
                Pos p={pos.x+dx[i],pos.y+dy[i]};
                Move temp={pos,p};
                res.push_back(temp);                   
                }   
            return res;
        }
        bool isValidMove(string board[8][8],Pos target){
            return (abs(target.x-pos.x)<2&&abs(target.y-pos.y)<2);
        }
};

class Bishop : public BasePies {
    public:
        Bishop(int x, int y, char color) : BasePies(x, y, color) {
            pieType = 'B';
        }
        vector<Move> getMoves(string board[8][8]){
            return getDiagonalMoves(board);
        }
        bool isValidMove(string board[8][8],Pos target){
            return isClearDiagonal(board,target);
        }
};

class Knight : public BasePies {
    public:
        Knight(int x, int y, char color) : BasePies(x, y, color) {
            pieType = 'N';
        }
        vector<Move> getMoves(string board[8][8]){
            vector<Move> res;
            char col=color==0?'W':'B';
            int dx[8]={-1,-1,1,1,-2,-2,2,2};
            int dy[8]={-2,+2,-2,2,1,-1,1,-1};

            for(int i=0;i<8;i++)
                if(isValidPos(pos.x+dx[i],pos.y+dy[i])&&board[pos.x+dx[i]][pos.y+dy[i]][1]!=col){
                Pos p={pos.x+dx[i],pos.y+dy[i]};
                Move temp={pos,p};
                res.push_back(temp);                   
                }
            return res;
        }
        bool isValidMove(string board[8][8],Pos target){
            return (abs(pos.x-target.x)==2&&abs(pos.y-target.y)==1)||(abs(pos.x-target.x)==1&&abs(pos.y-target.y)==2);
        }
};

class Queen : public BasePies {
    public:
        Queen(int x, int y, char color) : BasePies(x, y, color) {
            pieType = 'Q';
        }
        bool isValidMove(string board[8][8],Pos target){
            return isClearDiagonal(board,target)||isClearHorizontal(board,target)||isClearVertical(board,target);
        }
        vector<Move> getMoves(string board[8][8]){
            vector<Move> res,vertical,horizontal;
            res=getDiagonalMoves(board);
            vertical=getVerticalMoves(board);
            horizontal=getHorizontalMoves(board);
            res.insert(res.end(),vertical.begin(),vertical.end());
            res.insert(res.end(),horizontal.begin(),horizontal.end());
            return  res;
        }
};
class Pawn : public BasePies {
    public:
        Pawn(int x, int y, char color) : BasePies(x, y, color) {
            pieType = 'P';
        }
        bool isValidMove(string board[8][8],Pos target){
            int dx=color==0?-1:1;
            return (pos.x+dx==target.x&&abs(pos.y-target.y)==1);
        }
        vector<Move> getMoves(string board[8][8]){
            vector<Move> res;
            if(color==0){
                if(pos.x==6&&board[4][pos.y][0]=='-'&&board[5][pos.y][0]=='-'){
                    Pos p={pos.x-2,pos.y};
                    Move temp={pos,p};
                    res.push_back(temp);
                }
                if(board[pos.x-1][pos.y][0]=='-'){
                    Pos p={pos.x-1,pos.y};
                    Move temp={pos,p};
                    res.push_back(temp);
                }
                if(pos.y-1>-1&&board[pos.x-1][pos.y-1][1]=='B'){
                    Pos p={pos.x-1,pos.y-1};
                    Move temp={pos,p};
                    res.push_back(temp);
                }
                if(pos.y+1<8&&board[pos.x-1][pos.y+1][1]=='B'){
                    Pos p={pos.x-1,pos.y+1};
                    Move temp={pos,p};
                    res.push_back(temp);
                }
            }
            if(color==1){
                if(pos.x==1&&board[3][pos.y][0]=='-'&&board[2][pos.y][0]=='-'){
                    Pos p={pos.x+2,pos.y};
                    Move temp={pos,p};
                    res.push_back(temp);
                }
                if(board[pos.x+1][pos.y][0]=='-'){
                    Pos p={pos.x+1,pos.y};
                    Move temp={pos,p};
                    res.push_back(temp);
                }
                if(pos.y-1>-1&&board[pos.x+1][pos.y-1][1]=='W'){
                    Pos p={pos.x+1,pos.y-1};
                    Move temp={pos,p};
                    res.push_back(temp);
                }
                if(pos.y+1<8&&board[pos.x+1][pos.y+1][1]=='W'){
                    Pos p={pos.x+1,pos.y+1};
                    Move temp={pos,p};
                    res.push_back(temp);
                }
            }
            return  res;
        }

};

class Rook : public BasePies {
    public:
        Rook(int x, int y, char color) : BasePies(x, y, color) {
            pieType = 'R';
        }
        bool isValidMove(string board[8][8],Pos target){
            if(pos.x-target.x==0) return isClearHorizontal(board,target);
            else if(pos.y-target.y==0) return isClearVertical(board,target);
            else return false;
        }
        vector<Move> getMoves(string board[8][8]){
            vector<Move> res=getVerticalMoves(board),horizontal;
            horizontal=getHorizontalMoves(board);
            res.insert(res.end(),horizontal.begin(),horizontal.end());
            return res;
        }
};

class Board
{
  public:
    string board[8][8];
    BasePies *Pies[2][16];
    vector<Action> Actions;
    int pieCount[2],myColor,turn;
    Board(){
    istringstream is;
      string TM;
      cin>>TM;
      myColor=TM[0]=='W'?0:1;
      pieCount[0]=pieCount[1]=0;
      for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            cin>>board[i][j];
      char temp[2],color='W';
      BasePies *tempPie=new BasePies();
      for(int i=0;i<8;i++){
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
          }}
          if(TM[1]=='D')dMode(myColor);
          if(TM[1]=='M')mMode(myColor);
        // cout<<isCheckmate(1);
    }
    bool dMode(int color,int step=1){
        if(isCheckmate(color))return true;
        bool res=true;
        vector<string> result;
        switch (step)
        {
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
            break;
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
            break;
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
            break;
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
            break;
        }
        return res;
    }
    bool mMode(int color,int step=1){
        if(isCheckmate(!color))return true;
        bool res=true;
        vector<string> result;
        switch (step)
        {
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
            break;
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
            break;
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
            break;
        }
        return res;
    }
    void addPie(BasePies *pie){
      if(pie->color!=-1){
        pie->number=pieCount[pie->color];
        Pies[pie->color][pieCount[pie->color]]=pie;
        pieCount[pie->color]++;
      }
      board[pie->pos.x][pie->pos.y]=pie->name;
    }
    string convertPos(Pos pos){
      string res="a0";
      res[0]=(char)('a'+pos.y);
      res[1]='8'-pos.x;
      return res;
    }
    string convertMove(BasePies *pie,Move move){
      return convertPos(move.from)+pie->name+convertPos(move.to);
    }
    bool isValidMove(BasePies *piece,Move move){
      MovePie(piece,move.to);
      bool flag=isInCheck(piece->color);
      Undo();
      return !flag;
    }
    void MovePie(BasePies *piece,Pos target,char type='N'){
      if(target.x!=-1&&board[target.x][target.y]!="--"){
        int color=board[target.x][target.y][1]=='W'?0:1;
        BasePies *pie=Pies[color][getByPos(target.x,target.y)];
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
    void Undo(){
      if(Actions.size()==0) return;
      Action action=Actions.back();
      MovePie(Pies[action.color][action.number],action.move.from,'B');
      Actions.pop_back();
      if(Actions.size()==0) return;
      if(Actions.back().move.to.x==-1) Undo();
    }
    BasePies* getKing(int color){
      for(int i=0;i<pieCount[color];i++)
        if(Pies[color][i]->pieType=='K') return Pies[color][i];
      return new BasePies();
    }
    int getByPos(int x,int y){
      for(int i=0;i<pieCount[0];i++)
        if(Pies[0][i]->pos.x==x&&Pies[0][i]->pos.y==y) return i;
      for(int i=0;i<pieCount[1];i++)
        if(Pies[1][i]->pos.x==x&&Pies[1][i]->pos.y==y) return i;
      return 0;
    }
    vector<Move> getValidMoves(BasePies *piece){
        if(piece->pos.x==-1){
            vector<Move> res;
            return res;
        }
      vector<Move> temp=piece->getMoves(board),res;
      for(int i=0;i<temp.size();i++)
        if(isValidMove(piece,temp[i])) res.push_back(temp[i]);
      return res;
    }
    bool isInCheck(int color){
      BasePies *King=getKing(color);
      for(int i=0;i<pieCount[!color];i++){
        if(Pies[!color][i]->pos.x!=-1&&Pies[!color][i]->isValidMove(board,King->pos)) return true;
      }
      return false;
    }
    bool isCheckmate(int color){
        if(!isInCheck(color))return false;
      for(int i=0;i<pieCount[color];i++)
        if(getValidMoves(Pies[color][i]).size()!=0)return false;
      return true;
    }
};
int main()
{
    Board chess;
    return 0;
}
