#include "FlyThings.hpp"

FlyThings::FlyThings()
{
    Hut = {0,0,60,60};
    Springs[0] = {0,0,60,60};
    Springs[1] = {0,0,60,60};
    Jetpack[0] = {0,0,60,60};
    Jetpack[1] = {0,0,60,60};
    Jetpack[2] = {0,0,60,60};
    Jetpack[3] = {0,0,60,60};
    Jetpack[4] = {0,0,60,60};
    Jetpack[5] = {0,0,60,60};
    Jetpack[6] = {0,0,60,60};
    Jetpack[7] = {0,0,60,60};
    Jetpack[8] = {0,0,60,60};
}

void FlyThings::LoadImage(SDL_Renderer *renderer,std::string path)
{
    mTexture = IMG_LoadTexture(renderer,path.c_str());
}

void FlyThings::update(SDL_Renderer *renderer)
{
    width = getSprite()->w;
    height = getSprite()->h;
}

void FlyThings::SetType(int x)
{
    type = x;
    if(x == 0){     link_type = "Hut.png";}
    else if(x == 1){link_type = "springs.png";}
    else{           link_type = "jetpack.png";}
}

void FlyThings::render(SDL_Renderer *renderer,int x,int y,SDL_Rect *clip)
{
    SDL_Rect renderQuad = {x,y,width,height};

    if(clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopy( renderer,mTexture,clip,&renderQuad);
}

void FlyThings::animation_springs()
{

}

void FlyThings::animation_jetpack()
{

}

void FlyThings::animation_hut()
{

}

void FlyThings::free()
{
    if(mTexture != NULL){
        mTexture = NULL;
        posX = 0;posY = 0;
        width = 0;height = 0;
    }
}
