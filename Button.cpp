#include "Button.hpp"

Button::Button()
{
    button_type[0] = {0,0,140,50};
    button_type[1] = {140,0,140,50};
    button_type[2] = {140 * 2,0,140,50};
    button_type[3] = {140 * 3,0,140,50};
    button_type[4] = {140 * 4,0,140,50};
}

void Button::LoadImage(SDL_Renderer *renderer)
{
    free();
    if(type == -1){
        button_texture = IMG_LoadTexture(renderer,str_pause.c_str());
        width = 14;
        height = 19;
    }
    else button_texture = IMG_LoadTexture(renderer,str_button.c_str());
}

void Button::Render(SDL_Renderer *renderer)
{
    SDL_Rect RenderQuad = {posX,posY,140,50};
    if(type == -1)
        RenderQuad = {posX,posY,14,19};
    SDL_RenderCopy(renderer,button_texture,getRect(),&RenderQuad);
}

bool Button::handleEvent(SDL_Event *e)
{
    SDL_GetMouseState(&mouse_X,&mouse_Y);
    inside = true;

    if(mouse_X < posX){
        inside = 0;
    }
    else if(mouse_X > posX + width){
        inside = 0;
    }
    else if(mouse_Y  < posY){
        inside = 0;
    }
    else if(mouse_Y > posY + height){
        inside = 0;
    }
    return inside;
}

void Button::free()
{
    if(button_texture != nullptr)SDL_DestroyTexture(button_texture);
}
