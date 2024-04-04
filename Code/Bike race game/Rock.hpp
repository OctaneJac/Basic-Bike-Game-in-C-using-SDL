#pragma once
#include "SDL.h"
#include "unit.hpp"
#include "Roadobj.hpp"
#include <iostream>

class rock : public RoadObj
{

public:
    rock();
    rock(SDL_Texture *);
    void setrock();
    ~rock();
};
