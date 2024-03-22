#ifndef FlyThings_hpp
#define FlyThings_hpp

#include "Game.hpp"
#include <cmath>
class FlyThings{
private:
    int type = 0;
    std::string link_type = "";
    int width,height;
    int posX,posY,const_Y = 0;

    SDL_Texture *mTexture; // sprite
    SDL_Rect Springs[2];
    SDL_Rect Jetpack[10];
    SDL_Rect Hut[4];

    Mix_Chunk *feder = NULL;    bool once_feder = 0;
    Mix_Chunk *jetpack = NULL;  bool once_jetpack = 0;
    Mix_Chunk *propeller = NULL;bool once_propeller = 0;

    int current_frame_springs = 0,current_frame_jetpack = 9,current_frame_hut = 0;
    float animatedFPS = 24.0;
    Uint32 LastUpdate = 0.0,current; // time for animation
public:
    FlyThings();
    ~FlyThings();
    void LoadImage(SDL_Renderer *renderer);
    void render(SDL_Renderer *renderer,int x,int y, SDL_Rect *clip = NULL, double angel = 0.0,SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
    bool update(SDL_Renderer *renderer,int vY);
    bool endSelf();
    void handlevent(SDL_Event e);
    void animation_springs();
    void animation_hut(int x,int y);
    void animation_jetpack(int x,int y,int direction);
    void SetType(int x);
    void SetPosition(int x,int y){posX = x;posY = y;};
    void PreAnimation(){const_Y = posY;};
    void free();

    SDL_Rect *getSprite(){
        if(type == 0)return &Hut[current_frame_hut];
        else if(type == 1)return &Springs[current_frame_springs];
        return &Jetpack[current_frame_jetpack];
    }
    int getW(){return width;}
    int getH(){return height;}
    int getX(){return posX;}
    int getY(){return posY;}
    int getType(){return type;}
    int getFrame(){return current_frame_jetpack;};

};


#endif // FlyThings_hpp
