#ifndef FlyGroup_hpp
#define FlyGroup_hpp
#include "Game.hpp"
#include "FlyThings.hpp"
#include <vector>

class FlyGroup{
public:
    FlyGroup(){Fly_size = 0;}

    void add(FlyThings *fl){
        Fly.push_back(fl);
        Fly_size = Fly.size();
    }

    void remove_(int x){
        Fly[x]->free();
        Fly.erase(Fly.begin() + x);
        Fly_size = Fly.size();
    }

    void update(int vY,SDL_Renderer* renderer){
        if(!Fly.empty()){
            for(int i = Fly_size-1;i >= 0;i--){
                if(Fly[i]->update(renderer,vY)){

                }
            }
        }
    }

    void preAnimation(){
        if(!Fly.empty()){
            for(int i = Fly_size-1;i >= 0;i--){
                if(Fly[i] == sprite_collided) Fly[i]->PreAnimation();
            }
        }
    }

    void animation(int x,int y,int direction){
        if(!Fly.empty()){
            for(int i = Fly_size-1;i >= 0;i--){
                if(Fly[i] == sprite_collided){
                    if(Fly[i]->getType() == 0)Fly[i]->animation_hut(x + (direction ? 0 : 20),y - Fly[i]->getH() - 10);
                    else if(Fly[i]->getType() == 1)Fly[i]->animation_springs();
                    else{
                        Fly[i]->animation_jetpack(x,y,direction);
                    }
                }
            }
        }
    }

    void destroy_sprite(){
        if(!Fly.empty()){
            for(int i = Fly_size-1;i >= 0;i--){
                if(Fly[i] == sprite_collided && Fly[i]->getType() != 1){
                    remove_(i);
                }
            }
        }
    }

    int getType(){
        if(!Fly.empty()){
            for(int i = Fly_size-1;i >= 0;i--){
                if(Fly[i] == sprite_collided){
                    return Fly[i]->getType();
                }
            }
        }
        return 0;
    }


    bool CheckCollided(int x,int y,int DoodleSprite,int vY){
        collided = 0;
        for(int i = 0;i < Fly_size;i++){
            if(DoodleSprite == 0 || DoodleSprite == 2)if(   (x + 50 > Fly[i]->getX())                   && // <--
                                                            (x + 20 < Fly[i]->getX() + Fly[i]->getW()) &&
                                                            (y + 70 > Fly[i]->getY())                   &&
                                                            (y + 70 < Fly[i]->getY() + Fly[i]->getH()) &&
                                                            (vY > 0))collided = 1, sprite_collided = Fly[i];
            if(DoodleSprite == 1 || DoodleSprite == 3)if(   (x + 40 > Fly[i]->getX())                   && // -->
                                                            (x + 10 < Fly[i]->getX() + Fly[i]->getW()) &&
                                                            (y + 70 > Fly[i]->getY())                   &&
                                                            (y + 70 < Fly[i]->getY() + Fly[i]->getH()) &&
                                                            (vY > 0))collided = 1, sprite_collided = Fly[i];
        }
        return collided;
    }

    void auto_update(){
        for(int i = 0;i < Fly_size;i++){
//            if(Fly[i]->getType() == 1)Fly[i]->auto_update();
        }
    }

    void draw(SDL_Renderer* renderer,int direction){
        if(!Fly.empty()){
            for(int i = 0;i < Fly_size;i++){
                if(direction == 1 && Fly[i]->getFrame() != 9)Fly[i]->render(renderer,Fly[i]->getX(),Fly[i]->getY(),Fly[i]->getSprite(),0.0,NULL,SDL_FLIP_HORIZONTAL);
                else Fly[i]->render(renderer,Fly[i]->getX(),Fly[i]->getY(),Fly[i]->getSprite());
            }
        }
    }
    void clear_(){
        Fly.clear();
        Fly_size = 0;
    }

    int getSize(){return Fly_size;}
private:
    std::vector <FlyThings*> Fly;
    FlyThings* sprite_collided = nullptr;
    int Fly_size = 0;bool collided = 0;

};


#endif // FlyGroup_hpp
