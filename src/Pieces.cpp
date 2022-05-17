#include "Pieces.h"
using namespace std;

King::King(int x, int y, char color) : BasePies(x, y, color,'K'){}
Bishop::Bishop(int x, int y, char color) : BasePies(x, y, color,'B'){}
Knight::Knight(int x, int y, char color) : BasePies(x, y, color,'N'){}
Queen::Queen(int x, int y, char color) : BasePies(x, y, color,'Q'){}
Pawn::Pawn(int x, int y, char color) : BasePies(x, y, color,'P'){}
Rook::Rook(int x, int y, char color) : BasePies(x, y, color,'R'){}

bool King::isValidMove(string board[8][8],Pos target){
    return (abs(target.x-pos.x)<2&&abs(target.y-pos.y)<2);
}
bool Bishop::isValidMove(string board[8][8],Pos target){
    return isClearDiagonal(board,target);
}
bool Knight::isValidMove(string board[8][8],Pos target){
    return (abs(pos.x-target.x)==2&&abs(pos.y-target.y)==1)||(abs(pos.x-target.x)==1&&abs(pos.y-target.y)==2);
}
bool Queen::isValidMove(string board[8][8],Pos target){
    return isClearDiagonal(board,target)||isClearHorizontal(board,target)||isClearVertical(board,target);
}
bool Pawn::isValidMove(string board[8][8],Pos target){
    int dx=color==0?-1:1;
    return (pos.x+dx==target.x&&abs(pos.y-target.y)==1);
}
bool Rook::isValidMove(string board[8][8],Pos target){
    if(pos.x-target.x==0) return isClearHorizontal(board,target);
    else if(pos.y-target.y==0) return isClearVertical(board,target);
    else return false;
}

vector<Move> King::getMoves(string board[8][8]){
    vector<Move> res;
    char col=color==0?'W':'B';
    int dx[8]={1,1,1,0,0,-1,-1,-1},dy[8]={0,1,-1,-1,1,-1,1,0};
    for(int i=0;i<8;i++)
        if(isValidPos(pos.x+dx[i],pos.y+dy[i])&&board[pos.x+dx[i]][pos.y+dy[i]][1]!=col){
        Pos p={pos.x+dx[i],pos.y+dy[i]};
        Move temp={pos,p};
        res.push_back(temp);                   
        }   
    return res;
}
vector<Move> Bishop::getMoves(string board[8][8]){
    return getDiagonalMoves(board);
}
vector<Move> Knight::getMoves(string board[8][8]){
    vector<Move> res;
    char col=color==0?'W':'B';
    int dx[8]={-1,-1,1,1,-2,-2,2,2},dy[8]={-2,+2,-2,2,1,-1,1,-1};
    for(int i=0;i<8;i++)
        if(isValidPos(pos.x+dx[i],pos.y+dy[i])&&board[pos.x+dx[i]][pos.y+dy[i]][1]!=col){
        Pos p={pos.x+dx[i],pos.y+dy[i]};
        Move temp={pos,p};
        res.push_back(temp);                   
        }
    return res;
}
vector<Move> Queen::getMoves(string board[8][8]){
    vector<Move> res,vertical,horizontal;
    res=getDiagonalMoves(board);
    vertical=getVerticalMoves(board);
    horizontal=getHorizontalMoves(board);
    res.insert(res.end(),vertical.begin(),vertical.end());
    res.insert(res.end(),horizontal.begin(),horizontal.end());
    return  res;

}
vector<Move> Pawn::getMoves(string board[8][8]){
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
vector<Move> Rook::getMoves(string board[8][8]){
    vector<Move> res=getVerticalMoves(board),horizontal;
    horizontal=getHorizontalMoves(board);
    res.insert(res.end(),horizontal.begin(),horizontal.end());
    // concat two vectors
    
    return res;
}