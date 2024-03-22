#ifndef Monsterform_hpp
#define Monsterform_hpp

#include "Game.hpp"

class Monster{
public:
    Monster();
    ~Monster();
    void LoadImage(SDL_Renderer *renderer,std::string path);
    void render(SDL_Renderer *renderer,int x,int y, SDL_Rect *clip = NULL);
    void free();
    void animation();
    bool update(int vY);
    bool endSelf();
    void SetType(int t,SDL_Renderer *renderer);
    void SetPosition(int x,int y);
    void SetKilled(){killed = 1;}
    SDL_Rect* getSprite(int x){
        if(x <= 1)return &MonsterSprite[x];
        return &FlySprite[lastFrame];
    }
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

    Mix_Chunk *jumpOnMonster = NULL;bool jump_once = 0;
};

#endif // Monsterform_hpp
