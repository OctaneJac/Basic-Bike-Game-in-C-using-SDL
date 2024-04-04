#include "unit.hpp"
#include <iostream>
Unit::Unit() {}

void Unit::draw(SDL_Renderer *tex) // shared by all child classes which are rendered to the screen except for the main player bike, which has its own over ridden function.
{
    updatePos(); //updates position of the object, before rendering it to the screen.
    SDL_RenderCopy(tex, assets, &src, &mover);
}

void Unit::updatePos() {} 


bool operator == (Unit &c1, Unit &c2) //operator overload, to check if any two objects in the screen collide.
{
    SDL_Rect c1r = c1.getMover();   //get moverrects of objects
    SDL_Rect c2r = c2.getMover();   
    if (SDL_HasIntersection(&c1r, &c2r) == SDL_TRUE)
        return true;
    return false;
}

SDL_Rect Unit::getMover() // getter functions for mover, and mover.y, mover.x, mover.w and mover.h combined.
{
    return mover;
}
int Unit::getY()
{
    return mover.y;
}
int Unit::getX()
{
    return mover.x;
}
int Unit::getW()
{
    return mover.w;
}
int Unit::getH()
{
    return mover.h;
}
void Unit::setY(int k) //locate the object at a certain y level on the screen, setter for mover.y.
{
    mover.y = k;
}
Unit::~Unit() {}