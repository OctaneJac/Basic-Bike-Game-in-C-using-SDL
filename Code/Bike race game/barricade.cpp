#include "barricade.hpp"

barricade::barricade(){};

barricade::barricade(SDL_Texture *tex)
{
    s = 30;
    setbarricade(); //sets the source coordinates from the assets, for the selected type.
    lane = rand() % 4; //gives random lane to the created object.
    setPosition(); //sets the mover cooradinates for the selected lane.
    assets = tex;
}

barricade::~barricade()
{
}

void barricade::setbarricade()
{
    src = {38, 279, 112, 105};
}
