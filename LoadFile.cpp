#include "LoadFile.hpp"

SDL_Texture * TextureManager::getImage(SDL_Renderer *renderer,std::string texture)
{
    SDL_Surface *tempSurface = IMG_Load(texture.c_str());
    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer,tempSurface);
    SDL_FreeSurface(tempSurface);
    return tex;
}
