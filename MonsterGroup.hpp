#ifndef MonsterGroup_hpp
#define Monsterform_hpp

#include "Monsterform.hpp"
#include <vector>

class MonsterGroup{
public:
    MonsterGroup(){
        monsters_size = 0;
    };
    Monster* getBrick(int x){
        return MonsterSprites[x];
    }

    void add(Monster *monster){
        MonsterSprites.push_back(monster);
        monsters_size = MonsterSprites.size();
    }

    void remove_(int x){
        MonsterSprites[x]->free();
        MonsterSprites.erase(MonsterSprites.begin() + x);
        monsters_size = MonsterSprites.size();
    }

    void update(int vY,SDL_Renderer* renderer){
        if(!MonsterSprites.empty()){
            for(int i = monsters_size-1;i >= 0;i--){
                if(MonsterSprites[i]->update(vY)){
                    remove_(i);
                }
            }
        }
    }

    void endSelf(){
        if(!MonsterSprites.empty()){
            for(int i = monsters_size-1;i >= 0;i--){
                if(MonsterSprites[i]->endSelf()){
                    remove_(i);
                }
            }
        }
    }

    void animation(){
        if(!MonsterSprites.empty()){
            for(int i = monsters_size-1;i >= 0;i--){
                if(MonsterSprites[i] == collided_monster){
                    MonsterSprites[i]->SetKilled();
                }
                MonsterSprites[i]->animation();
            }
        }
    }

    int CheckCollided(int x,int y,int vY){
        collided = 0;
        for(int i = 0;i < monsters_size;i++){
            if( (x + 50 > MonsterSprites[i]->getX()) && // <--
                (x + 10 < MonsterSprites[i]->getX() + MonsterSprites[i]->getW()) &&
                (y + 70 >MonsterSprites[i]->getY())  &&
                (y + 70 < MonsterSprites[i]->getY() + MonsterSprites[i]->getH()) &&
                (vY > 0))collided = 1,collided_monster = MonsterSprites[i];
            else if( (x + 50 > MonsterSprites[i]->getX()) && // monster kill doodle
                (x + 10 < MonsterSprites[i]->getX() + MonsterSprites[i]->getW()) &&
                (((y + 57 > MonsterSprites[i]->getY()) &&
                (y  < MonsterSprites[i]->getY())) ||
                ((y < MonsterSprites[i]->getY() + MonsterSprites[i]->getH()) &&
                (y + 57 > MonsterSprites[i]->getY() + MonsterSprites[i]->getH())))
                )collided = 2;
        }
        return collided;
    }

    void auto_update(){
        for(int i = 0;i < monsters_size;i++){
//            if(MonsterSprites[i]->getType() == 3)MonsterSprites[i]->auto_update();
        }
    }

    void draw(SDL_Renderer* renderer){
        if(!MonsterSprites.empty()){
            for(int i = 0;i < monsters_size;i++){
//                std::cout << MonsterSprites[i]->getSprite(0) << '\n';
                MonsterSprites[i]->render(renderer,MonsterSprites[i]->getX(),MonsterSprites[i]->getY(),MonsterSprites[i]->getSprite(MonsterSprites[i]->getType()));
            }
        }
    }
    void clear_(){
        MonsterSprites.clear();
        monsters_size = 0;
    }

    int getSize(){return monsters_size;}
private:
    std::vector<Monster*> MonsterSprites;
    Monster *collided_monster = NULL;
    int collided;
    int monsters_size;
};

#endif // MonsterGroup_hpp


