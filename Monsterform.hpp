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

    int getX(){return posX;}
    int getY(){return posY;}
private:
    int posX,posY,const_X,const_Y;
    int velX,velY;
    int type;
    int vel_animation_X = 1;
    bool killed = 0;
    SDL_Rect MonsterSprite[3];
    SDL_Texture* mTexture;
    Uint32 LastUpdate,current;
};

#endif // Monsterform_hpp
