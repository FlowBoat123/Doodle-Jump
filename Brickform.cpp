#include "Brickform.hpp"
#include <cmath>

Brick::Brick()
{
    gSpriteBricks[0] = {0,0,75,20};
    gSpriteBricks[1] = {0,20,75,20};
    gSpriteBricks[2] = {0,20*2,75,20};
    gSpriteBricks[3] = {0,20*3,75,20};
    gSpriteBricks[4] = {0,20*4,75,20};
    gSpriteBricks[5] = {0,20*5,75,22};
    gSpriteBricks[6] = {0,20*5+22,75,35};
    gSpriteBricks[7] = {0,20*5+22+35,75,45};
}

Brick::~Brick()
{
}

void Brick::setPosition(int x,int y,int whichType)
{
    posX = x;
    posY = y;
    type = whichType;
    if(type == 4)breakk = Mix_LoadWAV("sounds/lomise.mp3");
    width = getSprite(type)->w;
    height = getSprite(type)->h;
}

bool Brick::update(int vY)
{
    posY -= vY;
    tempY -= vY;
    if(posY  > 700){
        free();
        return 1;
    }
    return 0;
}

bool Brick::endSelf()
{
    posY -= 10;tempY -= 5;
    if(posY < -50)return 1;
    return 0;
}

void Brick::collidedAnimation()
{
    Uint32 current = SDL_GetTicks();
    float time_diff = current - LastTouched;
    if(time_diff < 100.4)posY = tempY + 4;
    else posY = tempY;
}

void Brick::breakAnimation()
{
    Uint32 current = SDL_GetTicks();
    float time_diff = current - LastUpdate;
    if(lastFrame == 7)return;
    if(lastFrame == 4)Mix_PlayChannel(-1,breakk,0);
    if(time_diff > 50.4 && lastFrame != 7){
        lastFrame += 1;
        LastUpdate = current;
    }
}

void Brick::auto_update()
{
    if(posX > 300)velX = -2;
    if(posX < 30) velX = 2;
    posX += velX;
}

bool Brick::fall()
{
    posY += 8;
    if(posY > 700){
        free();
        return true;
    }
    return false;
}

bool Brick::LoadImage(SDL_Renderer *renderer,std::string path)
{
    mTexture = IMG_LoadTexture(renderer,path.c_str());
    return mTexture != NULL;
}

void Brick::render(SDL_Renderer *renderer,int x,int y, SDL_Rect *clip, double angel,SDL_Point* center, SDL_RendererFlip flip )
{
    SDL_Rect renderQuad = {x,y,clip->w,clip->h};
    SDL_RenderCopyEx( renderer,mTexture,clip,&renderQuad,angel,center,flip );
}

void Brick::free()
{
    if( mTexture != NULL )
	{
	    SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		width = 0;
		height = 0;
	}
	if(type == 4 && breakk != NULL){
        Mix_FreeChunk(breakk);
        breakk = NULL;
	}
}
