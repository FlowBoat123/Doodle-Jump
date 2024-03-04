#ifndef Monsterform_hpp
#define Monsterform_hpp

#include "Game.hpp"

class Monster{
public:
    Monster();
    void LoadImage(SDL_Renderer *renderer,std::string path);
    void render(SDL_Renderer *renderer,int x,int y, SDL_Rect *clip = NULL);
    void free();
    void animation();
    bool update(int vY);
    void Set(int x,int y,int t = 0);
    SDL_Rect* getSprite(int x){return &MonsterSprite[x];}
    SDL_Rect* getFrame(){return &FlySprite[lastFrame];}

    int getX(){return posX;}
    int getY(){return posY;}
    int getW(){return width;}
    int getH(){return height;}
    int getType(){return type;}
private:
    int posX,posY,const_X,const_Y;
    int velX,velY;
    int width,height;
    int type;
    int vel_animation_X = 1,vel_animation_Y = 2;
    bool killed = 0;
    float animatedFPS = 20.0f;
    short int lastFrame = 0;

    SDL_Rect MonsterSprite[2],FlySprite[3];
    SDL_Texture* mTexture;
    Uint32 LastUpdate,current,UpDownUpdate;
};

#endif // Monsterform_hpp
