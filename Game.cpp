#include "Game.hpp"
#include "doodle.hpp"
#include "real.hpp"
#include "Brickform.hpp"
#include "Monsterform.hpp"
#include "Score.hpp"
#include "Platform.hpp"

background *bg = nullptr;
Doodle *mc = nullptr;
Brick *br = nullptr;
Score_bar *score = nullptr;
Platform *Plat = nullptr;
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
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        renderer = SDL_CreateRenderer(window,-1,0);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        int imgFlags = IMG_INIT_JPG;
        if(!imgFlags){std::cout << "cant load images\n";} // Load image
        if( TTF_Init() == -1 ){ std::cout << "cant load ttf!\n"; }//Load ttf

        bg = new background();   bg->LoadImage(renderer,"background.png");
        mc = new Doodle();       mc->LoadImage(renderer,"doodle.png");

        score = new Score_bar();score->LoadImage(renderer,"top-score.png");score->LoadText(renderer,"Score : 0",{0,0,0});
        Plat = new Platform();

        for(int i = 0;i < 12;i++){
            br = new Brick();        br->LoadImage(renderer,"brick.png");
            br->setPosition(rand() % (width - 70),rand() % (height - 100));
//            br->setPosition(200,400);
            Plat->add(br);
        }
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

    mc->handleEvent(event);
}
bool collided;
void Game::update()
{
    //Doodle_Width = 58,Height = 57 | Doodle and brick inform | Brick_width = 70,height = 20;
    collided = 0;
    if(mc->getY() < border){//check if doodle cross the border
        score->PassBorder();
        Plat->update(mc->vY(),renderer);
        if(mc->vY() < 0){
            score->Plus(abs(mc->vY())); // update score
        }
        mc->scroll(border); // update pos doodle
    }
    else Plat->animation();
    Plat->auto_update();

    if(!score->isPassed() && mc->vY()<0){//change and update score
        score->Plus(abs(mc->vY()));
    }
    score->changeScore(score->getPoint());
    score->LoadText(renderer,score->getString(),{0,0,0});

    if(Plat->CheckCollided( mc->getX() , mc->getY() , mc->getDoodleSprite() , mc->vY() ))collided = 1; // update platform and collided
    mc->update(collided);
}

Game& Game::getInstance(){
    static Game instance;
    return instance;
}

void Game::render()
{
    SDL_RenderClear(renderer);
    bg->render(renderer,0,0);
    Plat->draw(renderer);

    mc->render(renderer,mc->getX(),mc->getY(),mc->getSprite(mc->getDoodleSprite()));
    score->renderBar(renderer,0,0);
    score->renderPoint(renderer,4,0);

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "cleaned";
}
