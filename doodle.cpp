#include "doodle.hpp"

Doodle::Doodle()
{
    mTexture = NULL;
    mwidth = 0;posX = 100;
    mheight = 0;posY = 300;
    gSpriteClips[0] = {0,0,58,57};      // <--
    gSpriteClips[1] = {58,0,58,57};     // -->
    gSpriteClips[2] = {58*2,0,58,57};   //jump animation <--
    gSpriteClips[3] = {58*3,0,58,57};   //jump animation -->
}

Doodle::~Doodle()
{}

bool Doodle::LoadImage(SDL_Renderer *renderer,std::string path)
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

void Doodle::update(bool collided)
{
//    std::cout << posX << ' ' << posY << '\n';
//    if(collided)std::cout << "collied\n";
    if(collided)lastCollided = SDL_GetTicks();//animation for doodle
    velY += 0.5;
    if(velY > 8){
        velY = 8;
    }
    if(posY >= 500 || collided){
        velY = -15;
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

//    std::cout << posY << ' ' << velY << '\n';
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

void Doodle::handleEvent(SDL_Event &e)
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_LEFT:  velX -= Doodle_Vel;direction = 0;break;
            case SDLK_RIGHT: velX += Doodle_Vel;direction = 1;break;
        }
    }
    else if(e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
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



