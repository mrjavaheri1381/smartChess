#include "Helper.h"

bool isValidPos(int x,int y){
    return x<8&&x>=0&&y>=0&&y<8;
}
std::string getPath(std::string piece){
    return "resources/images/Pieces/"+piece+".png";
}