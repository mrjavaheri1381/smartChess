#pragma once

#include <vector>
#include <string>
#include <iostream>

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

