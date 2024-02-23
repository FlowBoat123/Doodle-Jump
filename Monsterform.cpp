#include "Monsterform.hpp"

Monster::Monster()
{
    MonsterSprite[0] = {123,385,83,75};
    MonsterSprite[1] = {5,345,97,67};
}

void Monster::Set(int x,int y,int t)
{
    posX = x;const_X = x;
    posY = y;
    type = t;
}

void Monster::LoadImage(SDL_Renderer *renderer,std::string path)
{
    mTexture = IMG_LoadTexture(renderer,path.c_str());
}

void Monster::render(SDL_Renderer *renderer,int x,int y, SDL_Rect *clip)
{
    SDL_Rect renderQuad;
    renderQuad = {x,y,clip->w - 10,clip->h - 10};
    SDL_RenderCopy( renderer,mTexture,clip,&renderQuad );
}

void Monster::free()
{
    if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
	}
}

void Monster::animation()
{
    current = SDL_GetTicks();
    float time_diff = current - LastUpdate;
    if(time_diff < 200.0){
        posX = const_X + vel_animation_X;
    }
    else{
        vel_animation_X = -vel_animation_X;
        LastUpdate = current;
    }
}

bool Monster::update(int vY)
{
    posY += vY;
    if(posY > 600){
        free();
        return 1;
    }
    return 0;
}
