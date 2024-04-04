#pragma once
#include "SDL.h"
#include "Unit.hpp"

class bike : public Unit
{
    private:
        bool moveL;
        bool moveR;
        int moveFrame;
        SDL_Rect moverS;
        bool isDead;

        bool boost=false; 
        
        bike();
        static bike *instance;


public:
    float health = 5;
    int boostcounter=0;
    
    static bike *getInstance()
    {
    if (!instance)
    instance = new bike;
    return instance;
    }

    void setAssets(SDL_Texture *);
    void updatePos();
    void moveLeft();
    void moveRight();
    void activatebooster();
    
    void decHealth();
    void incHealth();
    int getHealth();
    void setHealth(int);

    void draw(SDL_Renderer *);

    void dead();
};