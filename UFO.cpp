#include "UFO.hpp"

UFO::UFO()
{
    clip_ufo[0] = {165,0,100,45};
    clip_ufo[1] = {266,0,100,154};
    lastUpdate = 0.0;updateFrame = 0.0;
}

SDL_Rect *UFO::getRect()
{
    Quad_ufo = {x,y,clip_ufo[curr_frame].w,clip_ufo[curr_frame].h};
    return &Quad_ufo;
}

void UFO::animation()
{
    current = SDL_GetTicks();
    if(current - lastUpdate >= 2000.0 && longg){
        longg = 0;
        lastUpdate = current;
        cnt++;
    }
    if(current - lastUpdate >= 1000.0 && !longg){
        cnt++;
        lastUpdate = current;
        if(cnt == 1)longg = 1;
    }
    if(cnt == 3){
        longg = 0;
        if(direct)direct = 0;
        else direct = 1;
        cnt = 0;
    }
    if(direct){
        if(!longg){
            x -= 0.25;
            y -= 0.25;
        }
        else{
            x -= 0.25;
            y += 0.25;
        }
    }
    else{
        if(!longg){
            x += 0.25;
            y -= 0.25;
        }
        else{
            x += 0.25;
            y += 0.25;
        }
    }
    if(current - updateFrame >= 1200.0){
        changeFrame = true;
        updateFrame = current;
        curr_frame = 1;
        double_flash = rand() % 2;
    }
    if(changeFrame){
        if(double_flash && current - updateFrame >= 79.0){
            double_flash = 0;
            curr_frame = 0;
            updateFrame = current;
        }
        else if(double_flash == 0 && curr_frame == 0 && current - updateFrame >= 30.0){
            curr_frame = 1;
            updateFrame = current;
        }
        else if(current - updateFrame >= 80.0){
            changeFrame = 0;
            curr_frame = 0;
        }
    }
}

void UFO::dvd_animation()
{

}

void UFO::LoadImage(SDL_Renderer *renderer)
{
    ufoTexture = IMG_LoadTexture(renderer,str_ufo.c_str());
}

void UFO::Render(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer,ufoTexture,&clip_ufo[curr_frame],getRect());
}

void UFO::free()
{
    if(ufoTexture != nullptr)SDL_DestroyTexture(ufoTexture);
}
