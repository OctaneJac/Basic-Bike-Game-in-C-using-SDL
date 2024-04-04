#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <list>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <sstream>
#include <vector>
#include "barricade.hpp"
#include "Patch.hpp"
#include "booster.hpp"
#include "money.hpp"
#include "bike.hpp"
#include "Tree.hpp"
#include "Rock.hpp"
#include "Cone.hpp"
using namespace std;

class Game
{
    //Screen dimension constants
    const int SCREEN_WIDTH = 1000;
    const int SCREEN_HEIGHT = 700;

    //vectors of pointers (dynamic objects) pf all objects to be rendered on the screen.
    vector<barricade *> bar; 
    vector<rock *>rr;
    vector<cone*>conero;
    
    vector<Patch *> pt;
    vector<booster *> boost;
    vector<money *> mon;
    vector<booster *> dis_ro;
    vector<Tree *> trees;
    
    bike *b=b->getInstance();

    bool gameover = false;
    bool quit = false;
    int screen = 2;

    SDL_Event e;

    //The window we'll be rendering to
    SDL_Window *gWindow = NULL;

    //The window renderer
    SDL_Renderer *gRenderer = NULL;

    //Current displayed texture
    SDL_Texture *gTexture = NULL;
    //global reference to png image sheets
    SDL_Texture *assets = NULL;

    //initializing font and setting text color
    TTF_Font *font = NULL;
    SDL_Color textColor = {1, 0, 0};

    //initialzing surface, texture and textrects to display varying numbers
    SDL_Surface *score_v = NULL;
    SDL_Texture *tscore_v = NULL;

    SDL_Surface *bikehealth = NULL;
    SDL_Texture *bikehealth_t=NULL;
    
    SDL_Surface *boostersurface = NULL;
    SDL_Texture *boostertexture = NULL;
    SDL_Rect boostertext;

    SDL_Rect texthealth, textscore;

    int ro = 0;
    int score = 0;

    Mix_Music *music = NULL;
    Mix_Chunk *chcollision = NULL;
    Mix_Chunk *chredcoin = NULL;
    Mix_Chunk *chcoin = NULL;
    bool music_ = false;
    
    int xMouse = 0, yMouse = 0;

public:
    bool init();
    bool loadMedia();
    void close();
    SDL_Texture *loadTexture(std::string path);
    void run();

    void populate_bg();
    void create_roadobjects();

    void treeLoad();
    void check_money(money *);
    void check_booster(booster *);

    template <typename V> 
    void deleteObjects(vector<V *> &);
    template <typename X> 
    void drawObjects(vector<X *> &);
    template <typename X> 
    void screenClear(vector<X *> &);
    
    void bike_collision();

    void displayScore();
    void displayMoney();
    
    void loadNew();

    void screen0();
    void screen2();
    void screen3();


};
