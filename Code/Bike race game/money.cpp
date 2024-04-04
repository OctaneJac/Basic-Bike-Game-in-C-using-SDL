#include "money.hpp"

money::money(){};

money::money(SDL_Texture *tex)
{
    s = 10;
    int temp = rand() % 100;
    if (temp < 5) //five percent probabilty for it to be a double coin
    {
        type = 0;
    }
    else if (temp < 60)
    {
        type = 2;
    }
    else
    {
        type = 1; 
    }
    setMoney(); //set source coordinates according to the file chosen
    lane = rand() % 4; //picking lane randomly
    setPosition(); //setting position according to the lane, this is called from parent class RoadObj
    assets = tex;
}

money::~money()
{
}

void money::setMoney() //setting the src coordinates according to type chosen.
{
    switch (type)
    {
    case 0:
        //coin *2
        src = {425,211,48,48};
        break;
    case 1:
        //standard coin
        src = {343,38,64,63};
        break;
    case 2:
        //negative coin
        src = {456,141,53,53};
        break;
    }
}
