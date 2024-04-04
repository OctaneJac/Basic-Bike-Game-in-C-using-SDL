#pragma once
#include "SDL.h"
#include "unit.hpp"

class Patch : public Unit //to make it appear like the lane lines on the screen are moving backwards.
{
    int id;

public:
    Patch();
    Patch(SDL_Texture*, int);
    void updatePos();
    void setPos();
    ~Patch();
};