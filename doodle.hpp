#ifndef doodle_hpp
#define doodle_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.hpp"

class Doodle{
public:
    static const int Doodle_Width = 58;
    static const int Doodle_Height = 57;

    static const int Doodle_Vel = 4;

    Doodle();
    ~Doodle();

    bool LoadImage(SDL_Renderer *renderer,std::string path);
    void render(SDL_Renderer *renderer,int x,int y, SDL_Rect *clip = NULL, double angel = 0.0,SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
    void update(int collided,bool died = 0);
    void SetPosition(double x,double y){posX = x;posY = y;}
    void animation();
    void free();
    void endSelf();
    void scroll(int &newHeight){posY = newHeight;}
    void SetFly(int type = 0);
    void SetJump(){big_jump = 1;};
    void SetTimeFall(){timeFall = SDL_GetTicks();};

    void handleEvent(SDL_Event *e);
    SDL_Rect* getSprite(int x){
         return &gSpriteClips[x];
    }

    int getwidth(){return mwidth;}
    int getheight(){return mheight;}
    int getX(){return posX;}
    int getY(){return posY;}
    int vY(){return velY;}
    int getDirection(){return direction;}
    bool isFlying(){return flying | big_jump;}
    bool isImmotal(){return immortal;}
    bool isDied(){return died;};
    bool isOver(){return over;};

    int getDoodleSprite();
private:
    SDL_Texture *mTexture;
    SDL_Rect gSpriteClips[4],FlySprites[4];
    int mwidth,mheight;
    double posX = 0,posY = 0;
    double velX = 0,velY = 0;
    bool flying = 0,big_jump = 0,jump_once = 0,immortal = 0;
    bool died = 0,over = 0;
    int frame_fly = 0,fly_type = 0;
    Uint32 lastUpdate,current;
    float time_limit_fly = 0.0;
    bool direction = 0;
    Uint32 lastCollided = 0.0,timeFall = 0.0; //set doodle sprite

    Mix_Chunk *jump = NULL;
    Mix_Chunk *crash = NULL;bool once_crash = 0;
    Mix_Chunk *fall = NULL;bool once_fall = 0;

};

#endif // real_hpp
