#include <iostream>
#include "Game.hpp"
using namespace std;

Game* game = nullptr;

int main(int argc,char *argv[])
{
    //initialize
    game = new Game();

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game->init("Doodle Jump",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,400,600,false);
    SDL_Renderer *renderer = game->getRenderer();

    while(game->running()){
        frameStart = SDL_GetTicks();
        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    game->clean();
    return 0;
}



