#include "Game.hpp"
#include "real.hpp"
#include "Level.hpp"
background *bg = nullptr;
Level *level = nullptr;
int border = 200;

Game::Game()
{
    window = NULL;
    renderer = NULL;
}
Game::~Game()
{}

bool Game::init(const char *title, int xpos,int ypos,int width, int height, bool fullscreen)
{
    int flags = 0;
    if(fullscreen)flags = 1;

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags); // create window
        renderer = SDL_CreateRenderer(window,-1,0);                         // create renderer

        int imgFlags = IMG_INIT_JPG;
        if(!imgFlags){std::cout << "cant load images\n";} // Load image
        if( TTF_Init() == -1 ){ std::cout << "cant load ttf!\n"; }//Load ttf

        level = new Level();
        level->init(renderer);
        level->LevelFromFile("Level1.txt");
        level->LoadLevel(renderer);

        isRunning = true;
    }else{
        isRunning = false;
    }
    return renderer != NULL;
}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
    level->HandleEvent(event);
}
bool collided;
void Game::update()
{
    level->Update(renderer);
}

Game& Game::getInstance(){
    static Game instance;
    return instance;
}

void Game::render()
{
    SDL_RenderClear(renderer);
    level->Render(renderer);
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "cleaned";
}
