#include "bike.hpp"

bike::bike()
{
    src = {397,288,62,99}; //source on png sheet
    mover = {530, 570, 60, 80};
    moveL = false;
    moveR = false;
    moveFrame = 0;
    isDead = false;
}

void bike::setAssets(SDL_Texture *tex)
{
    assets = tex;
}

void bike::moveLeft()
{
    if (mover.x > 250) //guard to prevent bike corssing the left side of the road
    {
        moveL = true;
    }
}
void bike::moveRight() //guard to prevent bike corssing the right side of the road
{
    if (mover.x < 670)
    {
        moveR = true;
    }
}

void ::bike::updatePos()
{
    if (!moveL && !moveR)
    {
        moveFrame = 0;
        src = {397,288,62,99};
    }
    else
    {
        if (boostcounter<=0)
        {

            if (moveL)
            {
                mover.x-=20;
                moveL = false;
            }
            if (moveR)
            {
                mover.x+=20;
                moveR = false;
            }

        }
        else
        {
            if (moveL)
            {
                mover.x-=90;
                moveL = false;
            }
            if (moveR)
            {
                mover.x+=90;
                moveR = false;
            }

            boostcounter--;
        }
    }
}

int bike::getHealth()
{
    return health;
}

void bike::decHealth()
{
    health-=0.08;
}

void bike::draw(SDL_Renderer *tex) //overriden draw function from unit class.
{
    updatePos();
    SDL_RenderCopy(tex, assets, &src, &mover);
}

void bike::dead() 
{
    isDead = true;
    mover.w = 100;
    mover.h = 50;
}

void bike::activatebooster()
{
    boostcounter=15;
}