#include "basePiece.h"

BasePies::BasePies(int x, int y,int color,char type) {
    pos.x = x;
    pos.y = y;
    this->pieType = type;
    this->color = color;
}
bool BasePies::isClearHorizontal(string board[8][8],Pos target){
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
bool BasePies::isClearVertical(string board[8][8],Pos target){
    if(pos.y!=target.y)return false;
    if(pos.x>target.x)
        for(int i=pos.x-1;i>target.x;i--)
            if(board[i][pos.y][1]!='-') return false;
    if(pos.x<target.x)
        for(int i=pos.x+1;i<target.x;i++)
            if(board[i][pos.y][1]!='-') return false;
    return true;
}
bool BasePies::isClearDiagonal(string board[8][8],Pos target){
    if(abs(pos.x-target.x)!=abs(pos.y-target.y))return false;
    int kx=pos.x>target.x?-1:1,ky=pos.y>target.y?-1:1;
    for(int i=1;;i++){
        if(pos.x+i*kx==target.x&&pos.y+i*ky==target.y)return true;  
        if(board[pos.x+kx*i][pos.y+i*ky][1]!='-') return false;     
    }
    return true;
}
vector<Move> BasePies::getDiagonalMoves(string board[8][8]){
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
vector<Move> BasePies::getVerticalMoves(string board[8][8]){
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
vector<Move> BasePies::getHorizontalMoves(string board[8][8]){
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
bool BasePies::isValidMove(string board[8][8],Pos target){return true;}
vector<Move> BasePies::getMoves(string board[8][8]){
    vector<Move> res;
    return res;
}
