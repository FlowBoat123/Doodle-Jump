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
//                    new_br = new Brick();
//                    new_br->LoadImage(renderer,"brick.png");
//                    new_br->setPosition(rand() % 330,0);
//                    add(new_br);
                }
            }
        }
    }

    void animation(){
        if(!MonsterSprites.empty()){
            for(int i = monsters_size-1;i >= 0;i--){
                MonsterSprites[i]->animation();
            }
        }
    }

    bool CheckCollided(int x,int y,int vY){
        collided = 0;
        for(int i = 0;i < monsters_size;i++){
            if( (x + 50 > MonsterSprites[i]->getX()) && // <--
                (x + 20 < MonsterSprites[i]->getX() + MonsterSprites[i]->getW()) &&
                (y + 70 >MonsterSprites[i]->getY())       &&
                (y + 70 < MonsterSprites[i]->getY() + MonsterSprites[i]->getH()) &&
                (vY > 0))collided = 1;
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
                MonsterSprites[i]->render(renderer,MonsterSprites[i]->getX(),MonsterSprites[i]->getY(),MonsterSprites[i]->getSprite(0));
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
    bool collided;
    int monsters_size;
};

#endif // MonsterGroup_hpp


