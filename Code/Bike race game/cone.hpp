#pragma once
#include "SDL.h"
#include "unit.hpp"
#include "Roadobj.hpp"
#include <iostream>

class cone: public RoadObj
{

public:
    cone();
    cone(SDL_Texture *);
    void setcone();
    ~cone();
};
