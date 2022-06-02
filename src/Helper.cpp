#include "Helper.h"
#include "iostream"
using namespace std;

bool isValidPos(int x,int y){
    return x<8&&x>=0&&y>=0&&y<8;
}
std::string getPath(std::string piece){
    std::string res="resources/images/Pieces/";
    piece.resize(2);
    res+=piece;
    return res+".png";
}