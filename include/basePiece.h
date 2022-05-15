#include "data.h"
using namespace std;
class BasePies{
    public:
        char pieType;
        int number,color;
        string name;
        Pos pos;
        BasePies(int , int ,int ,char);
        bool isClearHorizontal(string ,Pos );
        bool isClearVertical(string ,Pos );
        bool isClearDiagonal(string ,Pos );
        vector<Move> getDiagonalMoves(string );
        vector<Move> getVerticalMoves(string );
        vector<Move> getHorizontalMoves(string );
        virtual bool isValidMove(string ,Pos );
        virtual vector<Move> getMoves(string );
};