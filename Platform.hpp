#ifndef Platform_hpp
#define Platform_hpp
#include "Game.hpp"
#include "Brickform.hpp"
#include <vector>

class Platform{
public:
    Platform(){Plat_size = 0;}

    Brick* getBrick(int x){
        return Plat[x];
    }

    void add(Brick *brick){
        Plat.push_back(brick);
        Plat_size = Plat.size();
    }

    void remove_(int x){
        Plat[x]->free();
        Plat.erase(Plat.begin() + x);
        Plat_size = Plat.size();
    }

    void update(int vY,SDL_Renderer* renderer){
        if(!Plat.empty()){
            for(int i = Plat_size-1;i >= 0;i--){
                if(Plat[i]->update(vY)){
                    remove_(i);
                }
            }
        }
    }

    void animation(){
        if(!Plat.empty()){
            for(int i = Plat_size-1;i >= 0;i--){
                if(Plat[i] == brick_collided && !Plat[i]->isTouched()){
                    if(Plat[i]->getType() == 4){
                        Plat[i]->breakAnimation();
                    }
                    else
                        Plat[i]->collidedAnimation();
                }
            }
        }
    }

    bool CheckCollided(int x,int y,int DoodleSprite,int vY){
        collided = 0;
        for(int i = 0;i < Plat_size;i++){
            if(DoodleSprite == 0 || DoodleSprite == 2)if(   (x + 50 > Plat[i]->getX())                   && // <--
                                                            (x + 20 < Plat[i]->getX() + Plat[i]->getW()) &&
                                                            (y + 70 > Plat[i]->getY())                   &&
                                                            (y + 70 < Plat[i]->getY() + Plat[i]->getH()) &&
                                                            (vY > 0))collided = 1, brick_collided = Plat[i];
            if(DoodleSprite == 1 || DoodleSprite == 3)if(   (x + 40 > Plat[i]->getX())                   && // -->
                                                            (x + 10 < Plat[i]->getX() + Plat[i]->getW()) &&
                                                            (y + 70 > Plat[i]->getY())                   &&
                                                            (y + 70 < Plat[i]->getY() + Plat[i]->getH()) &&
                                                            (vY > 0))collided = 1, brick_collided = Plat[i];
        }
        if(collided){
//            std::cout << brick_collided->getType() << '\n';
            brick_collided -> preCollidedAnimation();
            if(brick_collided->getType() == 4)collided = 0;
        }

//        if(brick_collided->getType() == 4)collided = 0;
        return collided;
    }

    void auto_update(){
        for(int i = 0;i < Plat_size;i++){
            if(Plat[i]->getType() == 1)Plat[i]->auto_update();
        }
    }

    void draw(SDL_Renderer* renderer){
        if(!Plat.empty()){
            for(int i = 0;i < Plat_size;i++){
                Plat[i]->render(renderer,Plat[i]->getX(),Plat[i]->getY(),Plat[i]->getSprite(Plat[i]->getType()));
            }
        }
    }
    void clear_(){
        Plat.clear();
        Plat_size = 0;
    }

    int getSize(){return Plat_size;}
private:
    std::vector <Brick*> Plat;
    Brick *new_br = nullptr;
    bool collided;
    Brick *brick_collided = nullptr;
    int Plat_size;
};


#endif // Platform_hpp
