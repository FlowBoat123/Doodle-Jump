#include "Menu.hpp"

Menu::Menu()
{
    mc = new Doodle();
    mon = new Monster();

    clip_ufo[0] = {165,0,100,45};
    clip_ufo[1] = {266,0,100,154};

    clip_mc = {0,0,58,57};
}
SDL_Rect *Menu::getRect()
{
    Quad_ufo = {x,y,clip_ufo[curr_frame].w,clip_ufo[curr_frame].h};
    return &Quad_ufo;
}
void Menu::LoadImage(SDL_Renderer *renderer)
{
    free();
    bgTexture = IMG_LoadTexture(renderer,str_bg.c_str());
    ufoTexture = IMG_LoadTexture(renderer,str_ufo.c_str());
    mcTexture = IMG_LoadTexture(renderer,str_mc.c_str());
}

void Menu::init(SDL_Renderer *renderer)
{
    mc->SetPosition(48,200);
    mon->SetType(2,renderer);
    mon->SetPosition(50,130);
    x = 300;y = 45;
    lastUpdate = 0.0;updateFrame = 0.0;
}

void Menu::update(SDL_Renderer *renderer)
{
    if(mc->getY() > 450)mc->update(1,0);
    else mc->update(0,0);
    mon->animation();
    animation(renderer);
}


void Menu::animation(SDL_Renderer *renderer)
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

void Menu::Render(SDL_Renderer *renderer)
{
    SDL_Rect Quad_bg = {0,0,400,700};
    SDL_RenderCopy(renderer,bgTexture,NULL,&Quad_bg);

    SDL_Rect Quad_mc = {mc->getX(),mc->getY(),58,57};
    SDL_RenderCopy(renderer,mcTexture,&clip_mc,&Quad_mc);

    SDL_RenderCopy(renderer,ufoTexture,&clip_ufo[curr_frame],getRect());

    mon->render(renderer,mon->getX(),mon->getY(),mon->getSprite(2));
}

void Menu::free()
{
    if(bgTexture != nullptr)SDL_DestroyTexture(bgTexture);
    if(mcTexture != nullptr)SDL_DestroyTexture(mcTexture);
    if(monTexture != nullptr)SDL_DestroyTexture(monTexture);
    if(ufoTexture != nullptr)SDL_DestroyTexture(ufoTexture);
}
