#ifndef LoadFile_hpp
#define LoadFile_hpp

#pragma once
#include "Game.hpp"

class TextureManager{
public:
    static SDL_Texture *getImage(SDL_Renderer *renderer,std::string path);
    int getwidth(){return mwidth;}
    int getheight(){return mheight;}
private:
    int mwidth,mheight;
};

#endif // LoadFile_hpp
