#ifndef darkreal_hpp
#define darkreal_hpp

#include "Game.hpp"

class darkbg{
public:
    darkbg();
    void render(SDL_Renderer *renderer,int x,int y, SDL_Rect *clip = NULL);
    void update();
    void LoadImage(SDL_Renderer *renderer);
    void free(){
        if(bg != nullptr){
            SDL_DestroyTexture(bg);
            width = 0;
            height = 0;
        }
    };
private:
    SDL_Texture *bg;
    SDL_Texture *light_space_texture;
    SDL_Rect renderQuad[4];
    int width,height;
    std::string bg_str = "ghost-darkness.png",light_space_str = "ghost-darkness@2x.png";
};

#endif // darkreal_hpp
