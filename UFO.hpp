#ifndef UFO_hpp
#define UFO_hpp

#include "Game.hpp"

class UFO{
public:
    UFO();
    void LoadImage(SDL_Renderer *renderer);
    void Render(SDL_Renderer *renderer);
    void animation();
    void dvd_animation();
    void setPosition(int x_,int y_){x = x_;y = y_;};
    void free();
    SDL_Rect *getRect();
private:
    SDL_Texture *ufoTexture = nullptr;

    std::string str_ufo = "template/game-tiles.png";

    SDL_Rect clip_ufo[2];
    SDL_Rect Quad_ufo;

    double x = 0,y = 0;
    int direct = 1,cnt = 0,curr_frame = 0,double_flash = 0;
    bool longg = 0,up = 0,changeFrame = 0;
    Uint32 current,lastUpdate,updateFrame;
};

#endif // UFO_hpp
