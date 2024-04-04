#include "game.hpp"
#include "bike.hpp"
#include "Tree.hpp"
using namespace std;
#include <iostream>
bool Game::init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!");
        }

        //Create window
        gWindow = SDL_CreateWindow("Shapatar Rider", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }

                if (TTF_Init() == -1)
                {
                    return false;
                }

                //Initialize SDL_mixer
                if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
                {
                    return false;
                }
            }
        }
    }

    return success;
}

bool Game::loadMedia()
{
    //Loading success flag
    bool success = true;

    assets = loadTexture("assets4.png");
    gTexture = loadTexture("shapatar rider .png");

    //Opening the font and musics
    font = TTF_OpenFont("cooper.ttf", 30);
    music = Mix_LoadMUS("dhoom.mp3");
    chcollision = Mix_LoadWAV("collision.wav");
    chredcoin = Mix_LoadWAV("redcoin.wav");
    chcoin = Mix_LoadWAV("coin.wav");
    
    //setting display rects of text at position required
    texthealth = {185, 44, 50, 20};
    textscore = {170, 96, 40, 20};
    boostertext = {155,150,30,20};

    if (assets == NULL || gTexture == NULL)
    {
        printf("Unable to run due to error: %s\n", SDL_GetError());
        success = false;
    }

    return success;
}

void Game::close()
{
    //Free loaded images
    SDL_DestroyTexture(assets);
    assets = NULL;
    SDL_DestroyTexture(gTexture);

    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    //clearing all vectors of dynamic pointers
    screenClear(bar);
    screenClear(pt);
    screenClear(boost);
    screenClear(mon);
    screenClear(dis_ro);
    screenClear(trees);
    screenClear(rr);
    screenClear(conero);

    //closing font
    TTF_CloseFont(font);

    //Quit SDL subsystems
    TTF_Quit();
    Mix_Quit();

    IMG_Quit();
    SDL_Quit();
}

SDL_Texture *Game::loadTexture(std::string path)
{
    //The final texture
    SDL_Texture *newTexture = NULL;

    //Load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

void Game::populate_bg()
{ //initializes pointers of patches 
    for (int j = 0; j < 6; j++)
    {
        Patch *p = new Patch(assets, j);
        pt.push_back(p);
    }
}

void Game::create_roadobjects()
{ //randomly creates booster or money and adds it to its vector
    int r = rand() % 10;
    if (r < 5 and r>=0)
    {
         int y = rand() % 20;
         switch(y)
        {
             case(0):
            {
                barricade *v = new barricade(assets);
                bar.push_back(v);
                ro = 6;
                break;
             }
             case(1):
             {
                rock *rockvector = new rock(assets);
                rr.push_back(rockvector);
                ro = 9;
                break;
             }
            case(2):
             {
                cone *conevector = new cone(assets);
                conero.push_back(conevector);
                ro = 8;
                break;
             }
         }
    }
    else
    {
        int z = rand() % 10;
          switch(z)
        {
            case(0):
             {
                booster *bs = new booster(assets);
                boost.push_back(bs);
                ro = 4;
                break;
             }
            case(1):
             {
                money *m = new money(assets);
                mon.push_back(m);
                ro = 2;
                break;
             }
        }

    }
}

void Game::treeLoad()
{ // creates a tree
    if (rand() % 400 <= 10)
    {
        Tree *t = new Tree(assets);
        trees.push_back(t);
    }
}

template <typename X>
void Game::drawObjects(vector<X *> &vec)
{ // template function, to draw all road objects
    for (auto i = vec.begin(); i != vec.end(); i++)
    {
        (*i)->draw(gRenderer);
    }
}

template <typename V>
void Game::deleteObjects(vector<V *> &vec)
{ // template function, to delete all road objects
    auto i = vec.begin();
    while (i != vec.end())
    {
        if (((*i)->getY() >= 650) || ((*i)->getY() <= 5))
        {
            delete (*i);
            vec.erase(i);
        }
        else
        {
            ++i;
        }
    }
}

void Game::check_money(money *m)
{ // checks the type of money the biker has collided with from getType()
    int money_type = m->getType();

    if(money_type ==0)
    {
        score+=100;
    }
    else if(money_type==1)
    {   
        Mix_PlayChannel(-1,chcoin,0);
        score+=50;
    }
    else
    {   
        Mix_PlayChannel(-1, chredcoin, 0);
        score-=20;
    }
}

void Game::check_booster(booster *boost)
{
    int boosttype = boost->getType();
        if(boosttype == 0)
    {
        b->activatebooster();
    }
    else if(boosttype==1)
    {
        b->health++;
    }
}

void Game::bike_collision()
{ // checks bikes collision with different objects with the help of operator over-loaded collision function
    for (auto i = bar.begin(); i != bar.end(); i++)
    { // checks collision of bike with barricade
        if (*b == (*(*i)))
        {   
            Mix_PlayChannel(-1, chcollision, 0);
            cout<<"collision"<<endl;
            b->decHealth(); // minus health by 1.
        }
    }

    for (auto i = mon.begin(); i != mon.end(); i++)
    { // checks collision of bike with money
        if (*b == (*(*i)))
        {
            (*i)->setY(700);
            check_money((*i)); // sends to check_money to check type of money collided with
        }
    }
    for (auto i = boost.begin(); i != boost.end(); i++) //check for boosters.
    { 
        if (*b == (*(*i)))
        {
            (*i)->setY(700);
            check_booster((*i)); 
        }
    }
    for (auto i = rr.begin(); i != rr.end(); i++) //check for rock collision
    { 
        if (*b == (*(*i)))
        {   
            Mix_PlayChannel(-1, chcollision, 0);
            cout<<"collision"<<endl;
            b->decHealth(); 
        }
    }
    for (auto i = conero.begin(); i != conero.end(); i++) //check for cone collision
    { 
        if (*b == (*(*i)))
        {   
            Mix_PlayChannel(-1, chcollision, 0);
            cout<<"collision"<<endl;
            b->decHealth(); 
        }
    }
}

void Game::displayScore() // displays score and health on the screen.
{ 
    // converting score to strings for display.
    stringstream sc,hth,boost;
    sc << score; hth << int(b->getHealth()); boost<<b->boostcounter;

    // creating a surface of score and health
    score_v = TTF_RenderText_Solid(font, sc.str().c_str(), textColor);
    bikehealth = TTF_RenderText_Solid(font, hth.str().c_str(), textColor);
    boostersurface = TTF_RenderText_Solid(font, boost.str().c_str(), textColor);

    // creating texture of the surface of the score and health
    tscore_v = SDL_CreateTextureFromSurface(gRenderer, score_v);
    bikehealth_t = SDL_CreateTextureFromSurface(gRenderer, bikehealth);
    boostertexture = SDL_CreateTextureFromSurface(gRenderer, boostersurface);

    SDL_RenderCopy(gRenderer, tscore_v, NULL, &texthealth);
    SDL_RenderCopy(gRenderer, bikehealth_t, NULL, &textscore);
    SDL_RenderCopy(gRenderer, boostertexture, NULL, &boostertext);
    //displaying boost left.
}
    
template <typename X>
void Game::screenClear(vector<X *> &v1)
{ // used to traverse objects which are needed to be cleared from memory/screen when game ends/ new game is started. It makes use of the function delete objects.
    for (auto i = v1.begin(); i != v1.end(); i++)
    {
        (*i)->setY(750); //setting Y to 750 so that it can be deleted in the deleteobjects function
    }
    deleteObjects(v1);
}

void Game::screen0()
{ // in-game screen
    if (!music_)
    { //plays background music
        Mix_PlayMusic(music, -1);
        Mix_Volume(1, (MIX_MAX_VOLUME) / 8);
        music_ = true;
    }
    while (SDL_PollEvent(&e) != 0)
    {
        //User requests quit
        if (e.type == SDL_QUIT)
        {
            std::cout << "quit" << std::endl;
            quit = true;
        }

        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_LEFT)
        { // checks if left arrow key pressed
            b->moveLeft();
        }
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RIGHT)
        { // checks if right arrow key pressed
            b->moveRight();
        }

    }
    SDL_RenderClear(gRenderer);                      //removes everything from renderer
    SDL_RenderCopy(gRenderer, gTexture, NULL, NULL); //Draws background to renderer

    drawObjects(pt);   // draws patches
    b->draw(gRenderer); // draws bike
    treeLoad();        // loads trees
    if (ro == 0)
    { // creates road objects
        create_roadobjects();
    }
    else
    {
        ro--;
    }

    drawObjects(trees); // draws trees
    drawObjects(bar);   // draws vehicles
    drawObjects(conero);
    drawObjects(rr);
    drawObjects(boost); // draws boosters
    drawObjects(mon);   // draws money
    bike_collision();

    // deletes all vector pointers
    deleteObjects(trees);
    deleteObjects(bar);
    deleteObjects(boost);
    deleteObjects(mon);

    // calls function to display score
    displayScore();

    SDL_RenderPresent(gRenderer); //displays the updated renderer
    if (gameover)
    {
        gTexture = loadTexture("shapatar rider 2.png"); //Loads the pause background screen
        screen = 3;
    }
    if (b->getHealth() < 0.5)
    {
        
        b->dead();                    
        gameover = true;
    }

    SDL_Delay(100); //causes sdl engine to delay for specified miliseconds
}

void Game::screen2()
{ // main-menu
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            quit = true;
        }
        SDL_RenderClear(gRenderer);                      //removes everything from renderer
        SDL_RenderCopy(gRenderer, gTexture, NULL, NULL); //Draws background to renderer

        if (e.button.button == SDL_BUTTON_LEFT && e.type == SDL_MOUSEBUTTONDOWN) //CHECK LEFT CLICK
        {
            int xMouse, yMouse;
            SDL_GetMouseState(&xMouse, &yMouse);
            if (xMouse > 335 && yMouse > 288 && xMouse < 700 && yMouse < 335) //Start S
            {
                 // new game is being started, so all vectors/objects/variables are set to emptied/0/NULL
                gTexture = loadTexture("bg.jpeg");
                screen = 0;
            }
            else if (xMouse > 335 && yMouse > 506 && xMouse < 700 && yMouse < 550) //Exit
            {
                cout << "exit" << endl;
                quit = true;
            }
        }

        SDL_RenderPresent(gRenderer);
        SDL_Delay(100); //100 miliseconds
    }
    SDL_RenderPresent(gRenderer);
}
void Game::screen3()
{ // game-over

    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            quit = true;
        }
        SDL_RenderClear(gRenderer);                      //removes everything from renderer
        SDL_RenderCopy(gRenderer, gTexture, NULL, NULL); //Draws background to renderer
       

        SDL_RenderPresent(gRenderer);
        SDL_Delay(100);
    }
}
void Game::run()
{
    SDL_RenderClear(gRenderer);

    b->setAssets(assets);  // sets bike assets   
        // loads stationary road objects
    populate_bg();        // loads all background moving objects

    xMouse = 0, yMouse = 0;
    //While application is running
    while (!quit)
    {
        // calling respective function for screens
        if (screen == 0)
        {
            screen0();
        }
        else if (screen == 2)
        {
            screen2();
        }
        else if (screen == 3)
        {
            screen3();
        }
    }
}