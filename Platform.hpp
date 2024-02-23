#ifndef Platform_hpp
#define Platform_hpp
#include "Game.hpp"
#include "Brickform.hpp"
#include <vector>

class Platform{
public:
    Platform(){Plat_size = 0;}

    Brick* getBrick(int x){
        return PlatSprites[x];
    }

    void add(Brick *brick){
        PlatSprites.push_back(brick);
        Plat_size = PlatSprites.size();
    }

    void remove_(int x){
        PlatSprites[x]->free();
        PlatSprites.erase(PlatSprites.begin() + x);
        Plat_size = PlatSprites.size();
    }

    void update(int vY,SDL_Renderer* renderer){
        if(!PlatSprites.empty()){
            for(int i = Plat_size-1;i >= 0;i--){
                if(PlatSprites[i]->update(vY)){
                    remove_(i);
                    new_br = new Brick();
                    new_br->LoadImage(renderer,"brick.png");
                    new_br->setPosition(rand() % 330,0);
                    add(new_br);
                }
            }
        }
    }

    void animation(){
        if(!PlatSprites.empty()){
            for(int i = Plat_size-1;i >= 0;i--){
                if(PlatSprites[i] == brick_collided && !PlatSprites[i]->isTouched())PlatSprites[i]->collidedAnimation();
            }
        }
    }

    bool CheckCollided(int x,int y,int DoodleSprite,int vY){
        collided = 0;
        for(int i = 0;i < Plat_size;i++){
            if(DoodleSprite == 0 || DoodleSprite == 2)if( (x + 50 > PlatSprites[i]->getX()) && // <--
                                       (x + 20 < PlatSprites[i]->getX() + 68) &&
                                       (y + 70 >PlatSprites[i]->getY()) &&
                                       (y + 70 < PlatSprites[i]->getY() + 14) &&
                                                                    (vY > 0))collided = 1, brick_collided = PlatSprites[i];
            if(DoodleSprite == 1 || DoodleSprite == 3)if( (x + 40 > PlatSprites[i]->getX()) && // -->
                                       (x + 10 < PlatSprites[i]->getX() + 68) &&
                                       (y + 70 > PlatSprites[i]->getY()) &&
                                       (y + 70 < PlatSprites[i]->getY() + 14) &&
                                                                     (vY > 0))collided = 1, brick_collided = PlatSprites[i];
        }
        if(collided)brick_collided ->preCollidedAnimation();
        return collided;
    }

    void auto_update(){
        for(int i = 0;i < Plat_size;i++){
            if(PlatSprites[i]->getType() == 1)PlatSprites[i]->auto_update();
        }
    }

    void draw(SDL_Renderer* renderer){
        if(!PlatSprites.empty()){
            for(int i = 0;i < Plat_size;i++){
                PlatSprites[i]->render(renderer,PlatSprites[i]->getX(),PlatSprites[i]->getY(),PlatSprites[i]->getSprite(0));
            }
        }
    }
    void clear_(){
        PlatSprites.clear();
        Plat_size = 0;
    }

    int getSize(){return Plat_size;}
private:
    std::vector <Brick*> PlatSprites;
    Brick *new_br = nullptr;
    bool collided;
    Brick *brick_collided = nullptr;
    int Plat_size;
};


#endif // Platform_hpp
