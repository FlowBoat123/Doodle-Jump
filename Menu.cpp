#include "Menu.hpp"

Menu::Menu()
{
    mc = new Doodle();
    mon = new Monster();
    ufo = new UFO();
    button_play = new Button();
    button_quit = new Button();

    clip_mc = {0,0,58,57};
}

void Menu::LoadImage(SDL_Renderer *renderer)
{
    free();
    bgTexture = IMG_LoadTexture(renderer,str_bg.c_str());
    mcTexture = IMG_LoadTexture(renderer,str_mc.c_str());
}

void Menu::init(SDL_Renderer *renderer)
{
    mc->SetPosition(48,200);
    mc->LoadImage(renderer,str_mc.c_str());

    mon->SetType(2,renderer);
    mon->SetPosition(50,130);

    ufo->setPosition(300,45);
    ufo->LoadImage(renderer);

    button_play->LoadImage(renderer);
    button_quit->LoadImage(renderer);

    button_quit->SetPosition(250,450);
    button_quit->SetType(1);
    LoadImage(renderer);
}

void Menu::update(SDL_Renderer *renderer)
{
    if(mc->getY() > 450)mc->update(1,0);
    else mc->update(0,0);
    mon->animation();
    ufo->animation();
}

void Menu::handleEvent(SDL_Event *e)
{
    if(e->type == SDL_MOUSEBUTTONDOWN){
        if(button_play->handleEvent(e))play = 1;
        if(button_quit->handleEvent(e))quit = 1;
    }
}

void Menu::Render(SDL_Renderer *renderer)
{
    SDL_Rect Quad_bg = {0,0,400,700};
    SDL_RenderCopy(renderer,bgTexture,NULL,&Quad_bg);

    SDL_Rect Quad_mc = {mc->getX(),mc->getY(),58,57};
    SDL_RenderCopy(renderer,mcTexture,&clip_mc,&Quad_mc);

    ufo->Render(renderer);
    button_play->Render(renderer);
    button_quit->Render(renderer);
    mon->render(renderer,mon->getX(),mon->getY(),mon->getSprite(2));
}

void Menu::free()
{
    if(bgTexture != nullptr)SDL_DestroyTexture(bgTexture);
    if(mcTexture != nullptr)SDL_DestroyTexture(mcTexture);
}

Pause::Pause()
{
    ufo = new UFO();
    button_resume = new Button();
}

void Pause::init(SDL_Renderer *renderer)
{
    ufo->LoadImage(renderer);
    ufo->setPosition(220,100);

    button_resume->LoadImage(renderer);
    button_resume->SetType(2);
    button_resume->SetPosition(200,200);
    LoadImage(renderer);
}

void Pause::LoadImage(SDL_Renderer *renderer)
{
    bgTexture = IMG_LoadTexture(renderer,str_bg.c_str());
}

void Pause::update(SDL_Renderer *renderer)
{
    ufo->animation();
}

void Pause::handleEvent(SDL_Event *e)
{
    if(e->type == SDL_MOUSEBUTTONDOWN)
        if(button_resume->handleEvent(e))
            resume = 1;
    if(e->type == SDL_KEYDOWN)
        if(e->key.keysym.sym == SDLK_c)resume = 1;
}

void Pause::Render(SDL_Renderer *renderer)
{
    SDL_Rect Quad_bg = {0,0,400,700};
    SDL_RenderCopy(renderer,bgTexture,NULL,&Quad_bg);

    ufo->Render(renderer);
    button_resume->Render(renderer);
}

gameOver::gameOver()
{
    button_again = new Button();
}

void gameOver::LoadImage(SDL_Renderer *renderer)
{
    overBG_Texture = IMG_LoadTexture(renderer,str_over_bg.c_str());
}

void gameOver::init(SDL_Renderer *renderer)
{
    button_again->SetPosition(200,pY_again);
    button_again->SetType(4);
    button_again->LoadImage(renderer);
    LoadImage(renderer);
}

void gameOver::update()
{
    if(posY == 0)return;
    posY -= 10;
    pY_again -= 10;
    button_again->SetPosition(200,pY_again);
}

void gameOver::handleEvent(SDL_Event *e)
{
    if(e->type == SDL_MOUSEBUTTONDOWN){
        if(button_again->handleEvent(e))again = 1;
    }
}

void gameOver::Render(SDL_Renderer *renderer)
{
    SDL_Rect renderQuad = {posX,posY,400,700};
    SDL_RenderCopy(renderer,overBG_Texture,NULL,&renderQuad);

    button_again->Render(renderer);
}

void gameOver::free()
{

}

