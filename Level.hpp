#ifndef Level_hpp
#define Level_hpp
#include "Game.hpp"
#include "doodle.hpp"
#include "real.hpp"
#include "darkreal.hpp"
#include "Brickform.hpp"
#include "Monsterform.hpp"
#include "MonsterGroup.hpp"
#include "Score.hpp"
#include "Platform.hpp"
#include "FlyThings.hpp"
#include "Menu.hpp"
#include "FlyGroup.hpp"
#include "Button.hpp"
#include <vector>
#include <string>

class Level{
private:
    struct object{//posNtype
        int x,y;
        std::string type = "";
    };
    std::vector< std::vector<object> >Objects;
    std::vector< std::pair< int, std::vector<object> > > current_LV;
    int last_lv;
    bool once = 0,died = 0,collided_br = 0,outScreen = 0;
    int collided_mon = 0,num = 0,collided_fly_sprite = 0;
    int break_br = 0,moving_br = 0,fly_sprite = 0,springs = 0;
    int border = 300,fly_type = 0,monster_type = 0;
    int lastPoint = 0;
    bool flying = 0,dark_mode = 0,pause = 0;
    std::string cur_lv = "Level1.txt";
    Doodle *mc = nullptr;
    Brick *br = nullptr;
    Score_bar *score = nullptr;
    Platform *Plat = nullptr;
    Monster *monster = nullptr;
    MonsterGroup *monsters = nullptr;
    background *bg = nullptr;
    darkbg *dark_bg = nullptr;
    FlyThings *fl = nullptr;
    FlyGroup *fly_gr = nullptr;
    Button *pause_bt = nullptr;

public:
    Level();
    ~Level();

    int get_maxH(){return current_LV[last_lv-1].first;}
    int get_minH(){return current_LV[0].first;}

    void init(SDL_Renderer *renderer);
    void LevelFromFile(std::string lv_str);
    void updateLevel(SDL_Renderer *renderer);
    void LoadLevel(SDL_Renderer *renderer);
    void HandleEvent(SDL_Event *event);
    void MakeLevel(SDL_Renderer *renderer);
    void Update(SDL_Renderer *renderer);
    void Render(SDL_Renderer *renderer);
    void test(SDL_Renderer *renderer);
    void genFly(int t,SDL_Renderer *renderer,Brick *br);
    void genBrick(SDL_Renderer *renderer,int x,int y,int t);
    void updateBG(SDL_Renderer *renderer);
    void Continue(){pause = 0;};
    void reset();
    void fix();
    void free();

    int to_int(std::string s){
        num = 0;
        for(int i = 0;i < (int)s.size();i++){
            num = num * 10 + (s[i] - '0');
        }
        return num;
    }
    std::string getCurrentLV(){return cur_lv;}
    bool change_bg();
    bool isPause(){return pause;};
    bool isOver(){return mc->isOver();};
};

#endif // Level_hpp
