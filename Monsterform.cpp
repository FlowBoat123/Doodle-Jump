#include "Monsterform.hpp"
#include <cmath>

Monster::Monster()
{
    MonsterSprite[0] = {123,385,83,75};
    MonsterSprite[1] = {5,345,97,67};
    FlySprite[0] = {0,0,77,55}; // 1 fly animation
    FlySprite[1] = {78,0,77,55}; // 2
    FlySprite[2] = {79*2,0,77,55}; // 3
    jumpOnMonster = Mix_LoadWAV("sounds/jumponmonster.mp3");
}
Monster::~Monster()
{
    Mix_FreeChunk(jumpOnMonster);
    jumpOnMonster = NULL;
}

void Monster::SetType(int t,SDL_Renderer *renderer)
{
    type = t;
    width = getSprite(t)->w - 10;
    height = getSprite(t)->h - 10;
    if(t <= 1)LoadImage(renderer,"monsterTemplate.png");
    else LoadImage(renderer,"FlyMonster.png");
}

void Monster::SetPosition(int x,int y)
{
    posX = x;const_X = x;
    posY = y;const_Y = y;
}

void Monster::LoadImage(SDL_Renderer *renderer,std::string path)
{
    mTexture = IMG_LoadTexture(renderer,path.c_str());
}

void Monster::render(SDL_Renderer *renderer,int x,int y, SDL_Rect *clip)
{
    SDL_Rect renderQuad;
    renderQuad = {x,y,width,height};
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
    if(killed){
        if(!jump_once)Mix_PlayChannel(-1,jumpOnMonster,0),jump_once = 1;
        posY += 8;
        return;
    }
    current = SDL_GetTicks();
    float dT = (current - LastUpdate) / 1000.0f;
    int frametoUpdate = floor(dT / (1.0f / animatedFPS));
    float time_diff = current - UpDownUpdate;
    if(time_diff < 200.0){
        posX = const_X + vel_animation_X;
        posY = const_Y + vel_animation_Y;
    }
    else{
        vel_animation_X = -vel_animation_X;
        vel_animation_Y = -vel_animation_Y;
        UpDownUpdate = current;
    }
    if(frametoUpdate > 0){
        lastFrame += frametoUpdate;
        lastFrame %= 3;
//        std::cout << lastFrame << '\n';
        LastUpdate = current;
    }
}

bool Monster::update(int vY)
{
    posY -= vY;const_Y -= vY;
    if(posY > 700){
        free();
        return 1;
    }
    return 0;
}

bool Monster::endSelf()
{
    posY -= 10;const_Y -= 5;
    if(posY < -100)return 1;
    return 0;
}
