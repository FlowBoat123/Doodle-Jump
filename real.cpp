#include "real.hpp"
#include "LoadFile.hpp"

background::background()
{
    mTexture = NULL;
    mwidth = 0;
    mheight = 0;
}

background::~background()
{}

bool background::LoadImage(SDL_Renderer *renderer,std::string path)
{
    free();
    SDL_Texture *newTexture = NULL;
    SDL_Surface *loadedSurface = IMG_Load( path.c_str() );
    SDL_SetColorKey( loadedSurface,SDL_TRUE,SDL_MapRGB(loadedSurface->format,0,0xFF,0xFF) );
    newTexture = SDL_CreateTextureFromSurface( renderer,loadedSurface );
    mwidth = loadedSurface->w;
    mheight = loadedSurface->h;
    SDL_FreeSurface( loadedSurface );
    mTexture = newTexture;
    return mTexture != NULL;
}

void background::render(SDL_Renderer *renderer,int x,int y, SDL_Rect *clip)
{
    SDL_Rect renderQuad = {x,y,mwidth,mheight};
    if(clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopy( renderer,mTexture,clip,&renderQuad );
}

void background::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mwidth = 0;
		mheight = 0;
	}
}



