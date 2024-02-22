#include "Score.hpp"

Score_bar::Score_bar()
{
    mwidth = 450;gwidth = 0;
    mheight = 30;gheight = 0;
    Point = 0;
    mTexture = NULL;gTexture = NULL;
    under_h = 0;
    gFont = TTF_OpenFont("MSComicSans.ttf" , 16);
    if(gFont == NULL){
        std::cout << "cant load ttf!\n";
    }
    textCO = {0,0,0};
}

bool Score_bar::LoadText(SDL_Renderer *renderer,std::string path,SDL_Color textColor)
{
    free();
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, path.c_str(), textColor );
    gTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
    gwidth = textSurface -> w;
    gheight = textSurface -> h;
    SDL_FreeSurface( textSurface );
    return gTexture != NULL;
}

bool Score_bar::LoadImage(SDL_Renderer *renderer,std::string path)
{
    SDL_Texture *newTexture = NULL;
    SDL_Surface *loadedSurface = IMG_Load( path.c_str() );
    SDL_SetColorKey( loadedSurface,SDL_TRUE,SDL_MapRGB(loadedSurface->format,0,0xFF,0xFF) );
    newTexture = SDL_CreateTextureFromSurface( renderer,loadedSurface );
    SDL_FreeSurface( loadedSurface );
    mTexture = newTexture;
    return mTexture != NULL;
}

void Score_bar::renderBar(SDL_Renderer *renderer,int x,int y, SDL_Rect *clip)
{
    SDL_Rect renderQuad = {x,y,mwidth,mheight};
    if(clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopy( renderer,mTexture,clip,&renderQuad );
}

void Score_bar::renderPoint(SDL_Renderer *renderer,int x,int y,SDL_Rect *clip)
{
    SDL_Rect renderQuad = {x,y,gwidth,gheight};
    if(clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopy( renderer,gTexture,clip,&renderQuad );
}

void Score_bar::Plus(int x)
{
    Point += x;
}

void Score_bar::free()
{
	//Free texture if it exists
	if( gTexture != NULL )
	{
		SDL_DestroyTexture( gTexture );
		gTexture = NULL;
		gwidth = 0;
		gheight = 0;
	}
}
