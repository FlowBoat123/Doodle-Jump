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

bool background::LoadImage(SDL_Renderer *renderer)
{
    free();
    mTexture = IMG_LoadTexture(renderer,normal_bg.c_str());
    mwidth = 400;mheight = 640;
    return mTexture != NULL;
}

void background::render(SDL_Renderer *renderer,int x,int y, SDL_Rect *clip)
{
    SDL_Rect renderQuad = {x,y,mwidth,mheight};
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



