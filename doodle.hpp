#ifndef doodle_hpp
#define doodle_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Doodle{
public:
    static const int Doodle_Width = 58;
    static const int Doodle_Height = 57;

    static const int Doodle_Vel = 4;

    Doodle();
    ~Doodle();

    bool LoadImage(SDL_Renderer *renderer,std::string path);
    void render(SDL_Renderer *renderer,int x,int y, SDL_Rect *clip = NULL, double angel = 0.0,SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

    void update(bool collided = 0);
    void free();
    SDL_Rect* getSprite(int x){ return &gSpriteClips[x];}

    void handleEvent(SDL_Event &e);

    int getwidth(){return mwidth;}
    int getheight(){return mheight;}
    int getX(){return posX;}
    int getY(){return posY;}
    int vY(){return velY;}

    void scroll(int newHeight){posY = newHeight;}
    bool getDirection(){return direction;}
private:
    SDL_Texture *mTexture;
    SDL_Rect gSpriteClips[3];
    int mwidth,mheight;
    double posX,posY;
    double velX,velY;
    bool direction = 0;
};

#endif // real_hpp
