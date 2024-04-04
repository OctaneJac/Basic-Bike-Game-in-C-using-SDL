#pragma once
#include "SDL.h"
#include <iostream>

class Unit
{
    
    protected:
    SDL_Texture *assets;
    SDL_Rect src;
    SDL_Rect mover;
    
    public:
    
    Unit();
    virtual void updatePos();
    void draw(SDL_Renderer *);
    int getY();
    int getX();
    int getW();
    int getH();
    void setY(int);
    SDL_Rect getMover();
    friend bool operator ==(Unit &, Unit&);
    ~Unit();
};