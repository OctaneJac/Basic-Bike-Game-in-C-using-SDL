#pragma once
#include "Unit.hpp"

class RoadObj : public Unit
{//parent class for money, boosters and obstacles.
protected:
    int lane;
    int type;
    int s;
    float speed = 5;
    float size_inc = 1;
    bool stationary = false; 
    
public:
    RoadObj();
    void updatePos();
    void setPosition();
    int getType();
    ~RoadObj();
};