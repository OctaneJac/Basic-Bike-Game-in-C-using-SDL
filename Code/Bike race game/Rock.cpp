#include "Rock.hpp"

rock::rock(){};

rock::rock(SDL_Texture *tex)
{
    s = 20;
    setrock(); //sets the source coordinates from the assets
    lane = rand() % 4; //gives random lane to the rock
    setPosition(); //sets the mover cooradinates for the selected lane.
    assets = tex;
}

rock::~rock()
{
}

void rock::setrock()
{
    src = {34, 169, 72, 83};
}
