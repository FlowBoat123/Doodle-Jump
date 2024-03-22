#include "doodle.hpp"

Doodle::Doodle()
{
    mTexture = NULL;
    mwidth = 0; posX = 150;
    mheight = 0; posY = 400;

    jump = Mix_LoadWAV("sounds/jump.wav");
    crash = Mix_LoadWAV("sounds/monster-crash.mp3");
    fall = Mix_LoadWAV("sounds/pada.mp3");

    gSpriteClips[0] = {0,0,58,57};      // <--
    gSpriteClips[1] = {58,0,58,57};     // -->
    gSpriteClips[2] = {58*2,0,58,57};   //jump animation <--
    gSpriteClips[3] = {58*3,0,58,57};   //jump animation -->
}

Doodle::~Doodle()
{
    free();
    Mix_FreeChunk(jump); jump = NULL;
    Mix_FreeChunk(crash);crash = NULL;
    Mix_FreeChunk(fall); fall = NULL;
}

bool Doodle::LoadImage(SDL_Renderer *renderer,std::string path)
{
    mTexture = IMG_LoadTexture(renderer,path.c_str());
    return mTexture != NULL;
}

void Doodle::SetFly(int type)
{
    if(type == 1){
        big_jump = true;
        jump_once = 1;
        return;
    }
    lastUpdate = SDL_GetTicks();
    if(type == 0)time_limit_fly = 4000.0;
    else time_limit_fly = 7000.0;
    flying = true;
}

void Doodle::animation()
{
    current = SDL_GetTicks();
    if(current - lastUpdate > time_limit_fly){
        flying = false;
    }
}

void Doodle::update(int collided,bool died)
{
    if(collided == 1)lastCollided = SDL_GetTicks();//animation for doodle
    if(jump_once){
        velY = -25;
        jump_once = 0;
    }
    if(flying){
        velY = -10;      // fly
    }
    velY += 0.5;
    if(velY > 8){
        velY = 8;
    }
    if(/*posY >= 600 ||*/ (collided == 1 && !died)){
        velY = -15;
        big_jump = 0;
        Mix_PlayChannel(-1,jump,0);
    }
    if(collided == 2 && !isFlying()){ // die
        velY = 8;
        if(!once_crash)Mix_PlayChannel(-1,crash,0),once_crash = 1;
    }
    //update position
    posY += velY;
    posX += velX;

    //check if doodle outside screen

    if(posX > 400 - 20){
        posX = posX - 400;
    }
    if(posX + 30 < 0){
        posX = 400 - abs(posX);
    }
}

int Doodle::getDoodleSprite()
{
    Uint32 current = SDL_GetTicks();
    float animation = (current - lastCollided);
    if(animation < 350.0){
        return direction + 2;
    }
    return direction;
}

void Doodle::endSelf()
{
    Uint32 current = SDL_GetTicks();
    if(!once_fall)Mix_PlayChannel(-1,fall,0),once_fall = 1;
    if(current - timeFall > 3000.0)over = 1;
    if(current - timeFall <= 4000.0){
        posY -= 2;
        if(posY < 200)posY = 200;
        return;
    }

    posY += 8;
    died = 1;
    if(posY > 700)free();
}

void Doodle::handleEvent(SDL_Event *e)
{
    if(e->type == SDL_KEYDOWN && e->key.repeat == 0)
    {
        switch(e->key.keysym.sym)
        {
            case SDLK_LEFT:  velX -= Doodle_Vel;direction = 0;break;
            case SDLK_RIGHT: velX += Doodle_Vel;direction = 1;break;
        }
    }
    else if(e->type == SDL_KEYUP && e->key.repeat == 0)
    {
        switch(e->key.keysym.sym)
        {
            case SDLK_LEFT:  velX += Doodle_Vel;break;
            case SDLK_RIGHT: velX -= Doodle_Vel;break;
        }
    }
}

void Doodle::render(SDL_Renderer *renderer,int x,int y, SDL_Rect *clip, double angel,SDL_Point* center, SDL_RendererFlip flip )
{
    SDL_Rect renderQuad = {x,y,mwidth,mheight};

    if(clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopyEx( renderer,mTexture,clip,&renderQuad,angel,center,flip );
}

void Doodle::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
	}
}



