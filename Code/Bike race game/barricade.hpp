#pragma once
#include "SDL.h"
#include "unit.hpp"
#include "Roadobj.hpp"
#include <iostream>

class barricade : public RoadObj
{

public:
    barricade();
    barricade(SDL_Texture *);
    void setbarricade();
    ~barricade();
};
