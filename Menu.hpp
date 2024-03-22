#ifndef Menu_hpp
#define Menu_hpp

#include "Game.hpp"
#include "doodle.hpp"
#include "Monsterform.hpp"
#include "Button.hpp"
#include "UFO.hpp"

class Menu{
public:
    Menu();
    void LoadImage(SDL_Renderer *renderer);
    void Render(SDL_Renderer *renderer);
    void init(SDL_Renderer *renderer);
    void update(SDL_Renderer *renderer);
    void handleEvent(SDL_Event *e);
    void free();

    bool isQuit(){return quit;};
    bool isPlay(){return play;};
private:
    SDL_Texture *bgTexture = nullptr;
    SDL_Texture *mcTexture = nullptr;

    std::string str_bg = "covers/menu-cover.png";
    std::string str_mc = "doodle.png";

    SDL_Rect clip_mc;

    UFO *ufo = nullptr;
    Doodle *mc = nullptr;
    Monster *mon = nullptr;
    Button *button_play = nullptr,*button_quit = nullptr;

    bool quit = false,play = false;
};

class Pause{
public:
    Pause();
    void init(SDL_Renderer *renderer);
    void LoadImage(SDL_Renderer *renderer);
    void Render(SDL_Renderer *renderer);
    void handleEvent(SDL_Event *e);
    void update(SDL_Renderer *renderer);
    void SetPause(){resume = 0;}
    bool isContinue(){return resume;};

    void free();
private:
    SDL_Texture *bgTexture = nullptr;
    std::string str_bg = "covers/pause-bg.png";

    UFO *ufo = nullptr;
    Button *button_resume = nullptr;

    bool resume = 0;
};

class gameOver{
public:
    gameOver();
    void LoadImage(SDL_Renderer *renderer);
    void Render(SDL_Renderer *renderer);
    void init(SDL_Renderer *renderer);
    void handleEvent(SDL_Event *e);
    void update();
    bool isAgain(){return again;};
    void setAgain(){
        again = 0;
        posY = 700;
        pY_again = 700 + 400;
        button_again->SetPosition(0,700+400);
    };
    void free();

private:
    bool again = 0;
    SDL_Texture *overBG_Texture = nullptr;

    int posX = 0,posY = 700;
    int pY_again = 700+400;

    std::string str_over_bg = "covers/gameover-cover.png";
    std::string str_nor_bg = "covers/background.png";

    Button *button_again = nullptr;


};

#endif // Menu_hpp
