#include "darkreal.hpp"

darkbg::darkbg()
{

}

void darkbg::LoadImage(SDL_Renderer *renderer){
    free();
    bg = IMG_LoadTexture(renderer,bg_str.c_str());
    light_space_texture = IMG_LoadTexture(renderer,light_space_str.c_str());
    width = 400;height = 700;
};

void darkbg::render(SDL_Renderer *renderer,int x,int y, SDL_Rect *clip){
    renderQuad[1] = {0,0 ,400,800 - (800 - (y - 330))};
    renderQuad[2] = {x - 530,y - 330 ,1200,700};
    renderQuad[3] = {0,y - 330 + 700,400,700};

    SDL_RenderCopy( renderer,light_space_texture,clip,&renderQuad[2] );
    SDL_RenderCopy( renderer,bg,clip,&renderQuad[1] );
    SDL_RenderCopy( renderer,bg,clip,&renderQuad[3] );
}

