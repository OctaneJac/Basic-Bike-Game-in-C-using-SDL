#pragma once
#include "SDL.h"
#include "unit.hpp"
#include "Roadobj.hpp"
#include <iostream>

class money: public RoadObj
{

public:
    money();
    money(SDL_Texture *);
    void setMoney();
    ~money();
};