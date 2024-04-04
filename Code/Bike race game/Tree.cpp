#include "Tree.hpp"

Tree::Tree()
{
}
Tree::Tree(SDL_Texture *tex)
{
    assets = tex;
    setSrc(); //setting src coordinates accordingly
    side = rand() % 2; //random side chosen (left or right of the road.)
    if (side == 0)
    {
        mover.x = 250; //random x coordinate for each side of the road.
    }
    else
    {
        mover.x = 650;
    }
    mover.y = 350;
    mover.w = 100;
    mover.h = 160;
}

void Tree::setSrc()
{
    src = {219, 31, 92, 91};
}

void Tree::updatePos()
{ 
    mover.y += 8; //makes the trees go to the ends of the screen.
    if (side == 0)
    {
        mover.x -= 12;
    }
    else
    {
        mover.x += 12;
    }
    mover.w++;
    mover.h++;
}

Tree::~Tree() {}