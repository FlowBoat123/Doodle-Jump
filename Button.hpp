#ifndef Button_hpp
#define Button_hpp

#include "Game.hpp"

class Button{
public:
    Button();
    void LoadImage(SDL_Renderer *renderer);
    void SetPosition(int x,int y){posX = x;posY = y;};
    void SetType(int t){type = t;};
    void init(SDL_Renderer *renderer);
    void Render(SDL_Renderer *renderer);
    bool handleEvent(SDL_Event *e);
    void free();

    SDL_Rect *getRect(){
        if(type == -1)return NULL;
        return &button_type[type];
    };
private:
    SDL_Texture *button_texture = nullptr;
    SDL_Rect button_type[6];
    int type = 0;
    int posX = 120,posY = 150;
    int width = 140,height = 50;
    int mouse_X = 0,mouse_Y = 0;
    bool inside = true;
    std::string str_button = "buttons.png";
    std::string str_pause = "pause.png";
};

#endif // Button_hpp
