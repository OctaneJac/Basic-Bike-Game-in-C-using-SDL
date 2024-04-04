#include "Patch.hpp"
#include <iostream>

Patch::Patch() {}

Patch::Patch(SDL_Texture *tex, int i)
{
    id = i; //id as passed in the constructor, by default 6 patches on the road.
    assets = tex;
    src = {345, 145, 80, 48};
    setPos();
}

void Patch::setPos()
{   
    mover.h = 10; //setting initial positions accroding to their ids.
    mover.x = 480;
    switch (id)
    {
    case (0):
        mover = {482,480,15,8};
        break;
    case (1):
        mover = {482,520,50,8};
        break;
    case (2):
        mover = {482,560,50,8};
        break;
    case (3):
        mover = {482,600,50,8};
        break;
    case (4):
        mover = {482,640,50,8};
        break;
    case (5):
        mover = {482,680,50,8};
        break;
    }
    
}

void Patch::updatePos()
{
    mover.y += 8; //updating position and increasing in size so they move towards the player,
    mover.x -= 8;
    mover.w += 10;
    if (mover.y > 700)
    {
        mover =  mover={482,480,15,8}; //reappears at top of the road once they escape from bottom.
    }
}
Patch ::~Patch() {}