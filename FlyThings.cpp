#include "FlyThings.hpp"

FlyThings::FlyThings()
{
    Hut[0] = {0,0,65,50};
    Hut[1] = {65,0,55,50};
    Hut[2] = {0,60,55,50};
    Hut[3] = {65,60,55,50};

    Springs[0] = {0,0,26,20};
    Springs[1] = {0,20,26,38};

    Jetpack[0] = {8,0,21,41};
    Jetpack[1] = {40,0,17,49};
    Jetpack[2] = {71,0,18,54};
    Jetpack[3] = {99,0,23,62};
    Jetpack[4] = {2,64,26,62};
    Jetpack[5] = {34,64,28,62};
    Jetpack[6] = {72,64,14,56};
    Jetpack[7] = {104,64,14,49};
    Jetpack[8] = {8,128,14,44};
    Jetpack[9] = {40,128,13,36};
}

void FlyThings::LoadImage(SDL_Renderer *renderer)
{
    mTexture = IMG_LoadTexture(renderer,link_type.c_str());
}

bool FlyThings::update(SDL_Renderer *renderer,int vY)
{
    posY -= vY;
    const_Y -= vY;
    if(posY  > 700){
        free();
        return 1;
    }
    return 0;
}

void FlyThings::SetType(int x)
{
    type = x;
    if(x == 0){
        link_type = "Hut.png";
        width = 43;height = 25;
    }
    else if(x == 1){
        link_type = "springs.png";
        width = 26;height = 10;
//        std::cout << "liem\n";
    }
    else{
        link_type = "jetpack.png";
        width = Jetpack[current_frame_jetpack].w;height = Jetpack[current_frame_jetpack].h;
    }
}

void FlyThings::render(SDL_Renderer *renderer,int x,int y, SDL_Rect *clip, double angel,SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = {x,y,width,height};
//    std::cout << x << ' ' << y << '\n';

    if(type == 0)
    {
        renderQuad.w = clip->w - 22;
        renderQuad.h = clip->h - 17;
    }
    SDL_RenderCopyEx( renderer,mTexture,clip,&renderQuad,angel,center,flip );
}

void FlyThings::animation_springs()
{
    current = SDL_GetTicks();
    if(LastUpdate - current > 0.600){
        current_frame_springs = 1;
        SetPosition(posX,const_Y - 12);
    }
}

void FlyThings::animation_jetpack(int x,int y,int direction) // 0 for --> and 1 for <--
{
    if(!direction)SetPosition(x + 49,y);
    else SetPosition(x - 10,y);
    current = SDL_GetTicks();
    float dT = (current - LastUpdate) / 1000.0f;
    int frametoUpdate = floor(dT / (1.0f / animatedFPS));
    if(frametoUpdate > 0){
        current_frame_jetpack += frametoUpdate;
        current_frame_jetpack %= 9;
        if(!current_frame_jetpack)current_frame_jetpack = 1;
        LastUpdate = current;
    }
    width = Jetpack[current_frame_jetpack].w;
    height = Jetpack[current_frame_jetpack].h;
    switch (current_frame_jetpack)
    {
    case 0:
        if(!direction)SetPosition(x + 55,y);
        else SetPosition(x - 18,y);
        break;
    case 1:
        if(!direction)SetPosition(x + 55,y);
        else SetPosition(x - 14,y);
        break;
    case 2:
        if(!direction)SetPosition(x + 54,y);
        else SetPosition(x - 14,y);
        break;
    case 3:
        if(!direction)SetPosition(x + 50,y);
        else SetPosition(x - 15,y);
        break;
    case 4:
        if(!direction)SetPosition(x + 50,y);
        else SetPosition(x - 15,y);
        break;
    case 5:
        if(!direction)SetPosition(x + 50,y);
        else SetPosition(x - 19,y);
        break;
    case 6:
        if(!direction)SetPosition(x + 55,y);
        else SetPosition(x - 12,y);
        break;
    case 7:
        if(!direction)SetPosition(x + 55,y);
        else SetPosition(x - 12,y);
        break;
    case 8:
        if(!direction)SetPosition(x + 55,y);
        else SetPosition(x - 12,y);
        break;
    }

}

void FlyThings::animation_hut(int x,int y)
{
    SetPosition(x,y);
    current = SDL_GetTicks();
    float dT = (current - LastUpdate) / 1000.0f;
    int frametoUpdate = floor(dT / (1.0f / animatedFPS));
    if(frametoUpdate > 0){
        current_frame_hut += frametoUpdate;
        current_frame_hut %= 4;
        if(!current_frame_hut)current_frame_hut = 1;
        LastUpdate = current;
    }
}

void FlyThings::free()
{
    if(mTexture != NULL){
        mTexture = NULL;
        posX = 0;posY = 0;
        width = 0;height = 0;
    }
}
