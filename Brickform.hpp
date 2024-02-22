#ifndef Brickform_hpp
#define Brickform_hpp

#include "Game.hpp"

class Brick{
public:
    Brick();
    bool LoadImage(SDL_Renderer *renderer,std::string path);
    void render(SDL_Renderer *renderer,int x,int y, SDL_Rect *clip = NULL, double angel = 0.0,SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
    void free();
    bool update(int vY = 0);
    void auto_update();
    void setPosition(int x,int y,int whichtype = 0);

    SDL_Rect* getSprite(int x){ return &gSpriteBricks[x];}

    int getwidth(){return mwidth;}
    int getheight(){return mheight;}
    int getX(){return posX;}
    int getY(){return posY;}
    int getType(){return type;}
private:
    SDL_Texture *mTexture;
    SDL_Rect gSpriteBricks[8];
    int mwidth,mheight;
    int posX,posY;
    int velX = 2;
    int type;
};


#endif // Brickform_hpp

