#ifndef FlyThings_hpp
#define FlyThings_hpp

#include "Game.hpp"

class FlyThings{
private:
    int type = 0;
    std::string link_type = "";
    int width,height;
    int posX,posY;

    SDL_Texture *mTexture; // sprite
    SDL_Rect Springs[2];
    SDL_Rect Jetpack[8];
    SDL_Rect Hut;

    int current_frame_springs = 0,current_frame_jetpack = 0;

    Uint32 lastUpdate,current; // time for animation
public:
    FlyThings();
    void LoadImage(SDL_Renderer *renderer,std::string path);
    void render(SDL_Renderer *renderer,int x,int y,SDL_Rect *clip = NULL);
    void update(SDL_Renderer *renderer);
    void handlevent(SDL_Event e);
    void animation_springs();
    void animation_hut();
    void animation_jetpack();
    void SetType(int x);
    void SetPosition(int x,int y){posX = x;posY = y;};
    void free();

    SDL_Rect *getSprite(){
        if(type == 0)return &Hut;
        else if(type == 1)return &Springs[current_frame_springs];
        return &Jetpack[current_frame_jetpack];
    }
    int getW(){return width;}
    int getH(){return height;}
    int getX(){return posX;}
    int getY(){return posY;}

};


#endif // FlyThings_hpp
