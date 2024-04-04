#include "booster.hpp"

booster::booster(){};

booster::booster(SDL_Texture *tex)
{// normal booster is constructed
    type = rand() % 2;

    setBooster();
    lane = rand() % 4;
    setPosition();
    assets = tex;
}

booster::~booster()
{
}

void booster::setBooster()
{
    switch (type)
    {
    case 0:
        //turbo booster
        src = {127, 130, 60, 70};
        break;
    case 1:
        //Extra Health
        src = {204, 200, 56, 57};
        break;
    }
}
