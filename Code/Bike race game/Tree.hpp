#pragma once
#include "Unit.hpp"

class Tree:public Unit{
    int side;
    int type;
    public:
    Tree();
    Tree(SDL_Texture*);
    void setSrc();
    void updatePos();
    ~Tree();
};