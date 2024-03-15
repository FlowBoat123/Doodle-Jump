#ifndef Menu_hpp
#define Menu_hpp

#include "Game.hpp"
#include "doodle.hpp"
#include "Monsterform.hpp"

class Menu{
public:
    Menu();
    void LoadImage(SDL_Renderer *renderer);
    void Render(SDL_Renderer *renderer);
    void init(SDL_Renderer *renderer);
    void update(SDL_Renderer *renderer);
    void animation(SDL_Renderer *renderer);
    void free();

    SDL_Rect *getRect();

private:
    SDL_Texture *bgTexture = nullptr;
    SDL_Texture *mcTexture = nullptr;
    SDL_Texture *ufoTexture = nullptr;
    SDL_Texture *monTexture = nullptr;

    std::string str_bg = "covers/menu-cover.png";
    std::string str_mc = "doodle.png";
    std::string str_ufo = "template/game-tiles.png";

    SDL_Rect clip_mc;
    SDL_Rect clip_ufo[2];
    SDL_Rect Quad_ufo;

    Doodle *mc;
    Monster *mon;

    double x = 0,y = 0;
    int direct = 1,cnt = 0,curr_frame = 0,double_flash = 0;
    bool longg = 0,up = 0,changeFrame = 0;
    Uint32 current,ncurrent,lastUpdate,updateFrame;
};

#endif // Menu_hpp
