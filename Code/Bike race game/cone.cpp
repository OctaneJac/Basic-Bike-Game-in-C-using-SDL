#include "cone.hpp"

cone::cone(){};

cone::cone(SDL_Texture *tex)
{
    s = 20;
    setcone(); //sets the source coordinates from the assets
    lane = rand() % 4; //gives random lane to the created object.
    setPosition(); //sets the mover cooradinates for the selected lane.
    assets = tex;
}

cone::~cone()
{
}

void cone::setcone()
{
    src = {444, 44, 56, 57};
}
