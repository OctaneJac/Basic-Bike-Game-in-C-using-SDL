#include "Roadobj.hpp"

RoadObj::RoadObj() {}
void RoadObj::updatePos()
{
    if (!stationary)//position is only updated if objects are not stationary. x.coordinates are adjusted according to the lane.
    {
        switch (lane)
        {
        case (0):
            mover.x -= 5;
            break;
        case (1):
            mover.x -= 2;
            break;
        case (2):
            mover.x += 1;
            break;
        case(3):
            mover.x+=5;
            break;
        }
        mover.y += int(speed); 
        speed += 0.01;
        mover.w += int(size_inc); //objects enlarge is size a little as they move towards the biker, as if they are coming closer,
        mover.h += int(size_inc);
        size_inc += 0.05;
    }
}

void RoadObj::setPosition()
{
    switch (lane) //sets the position according to the lane they are in.
    {
    case (0):
        mover = {455, 450, s, s};
        break;
    case (1):
        mover = {478, 450, s, s};
        break;
    case (2):
        mover = {483, 450, s, s};
        break;
    case (3):
        mover = {495, 450, s, s};
        break;
    }
}

int RoadObj::getType() //getter function for type 
{
    return type;
}

RoadObj::~RoadObj() {}