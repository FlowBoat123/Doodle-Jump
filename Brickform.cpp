#include "Brickform.hpp"

Brick::Brick()
{
    gSpriteBricks[0] = {0,50*0,170,50};
    gSpriteBricks[1] = {0,50*1,170,50};
    gSpriteBricks[2] = {0,50*2,170,50};
    gSpriteBricks[3] = {0,50*3,170,50};
    gSpriteBricks[4] = {0,50*4,170,50};
    gSpriteBricks[5] = {0,50*5,170,50};
    gSpriteBricks[6] = {0,50*6,170,50};
    gSpriteBricks[7] = {0,50*7,170,50};
}

void Brick::setPosition(int x,int y,int whichType)
{
    posX = x;
    posY = y;
    type = whichType;
}

bool Brick::update(int vY)
{
    posY -= vY;
    tempY -= vY;
    if(posY  > 600){
        free();
        return 1;
    }
    return 0;
}

void Brick::collidedAnimation()
{

    Uint32 current = SDL_GetTicks();
    float animation = current - LastTouched;
    if(animation < 100.4)posY = tempY + 4;
    else posY = tempY;
//    std::cout << posY << ' ' << tempY << '\n';
}

void Brick::auto_update()
{
    if(posX > 300)velX = -2;
    if(posX < 30) velX = 2;
    posX += velX;
}

bool Brick::LoadImage(SDL_Renderer *renderer,std::string path)
{
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

void Brick::render(SDL_Renderer *renderer,int x,int y, SDL_Rect *clip, double angel,SDL_Point* center, SDL_RendererFlip flip )
{
    SDL_Rect renderQuad = {x,y,mwidth,mheight};

    if(clip != NULL)
    {
        renderQuad.w = 70;
        renderQuad.h = 20;
    }
    SDL_RenderCopyEx( renderer,mTexture,clip,&renderQuad,angel,center,flip );
}

void Brick::free()
{
    if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mwidth = 0;
		mheight = 0;
	}
}
