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
//                    std::cout << i << '\n';
                    new_br = new Brick();
//                    std::cout << new_br << '\n';
                    new_br->LoadImage(renderer,"brick.png");
                    new_br->setPosition(rand() % 330,0);
                    add(new_br);
                }
            }
        }
    }

    bool CheckCollided(int x,int y,int direction){
//        std::cout << x << ' ' << y << ' ' << direction << '\n';
        for(int i = 0;i < Plat_size;i++){
//            std::cout << i << '\n';
            if(direction == 0)if( (x + 50 > PlatSprites[i]->getX()) && // <--
                                       (x + 20 < PlatSprites[i]->getX() + 68) &&
                                       (y + 70 >PlatSprites[i]->getY()) &&
                                       (y + 70 < PlatSprites[i]->getY() + 14))return 1;
            if(direction == 1)if( (x + 40 > PlatSprites[i]->getX()) && // -->
                                       (x + 10 < PlatSprites[i]->getX() + 68) &&
                                       (y + 70 > PlatSprites[i]->getY()) &&
                                       (y + 70 < PlatSprites[i]->getY() + 14))return 1;
        }
        return 0;
    }

    void auto_update(){
        for(int i = 0;i < Plat_size;i++){
            if(PlatSprites[i]->getType() == 0)PlatSprites[i]->auto_update();
        }
    }

    void draw(SDL_Renderer* renderer){
        if(!PlatSprites.empty()){
            for(int i = 0;i < Plat_size;i++){
                PlatSprites[i]->render(renderer,PlatSprites[i]->getX(),PlatSprites[i]->getY(),PlatSprites[i]->getSprite(0));
//                std::cout << PlatSprites[i]->getX() << ' ' << PlatSprites[i]->getY() << '\n';
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
    int Plat_size;
};


#endif // Platform_hpp
