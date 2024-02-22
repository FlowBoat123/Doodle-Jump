#ifndef real_hpp
#define real_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class background{
public:
    background();
    ~background();

    bool LoadImage(SDL_Renderer *renderer,std::string path);
    void free();
    void render(SDL_Renderer *renderer,int x,int y, SDL_Rect *clip = NULL);

    void update();

    int getwidth(){return mwidth;}
    int getheight(){return mheight;}
private:
    SDL_Texture *mTexture;
    int mwidth;
    int mheight;
};

#endif // real_hpp
