#ifndef Level_hpp
#define Level_hpp
#include "Game.hpp"
#include "doodle.hpp"
#include "real.hpp"
#include "Brickform.hpp"
#include "Monsterform.hpp"
#include "MonsterGroup.hpp"
#include "Score.hpp"
#include "Platform.hpp"
#include <vector>
#include <string>

class Level{
private:
    struct object{//posNtype
        int x,y;
        std::string type = "";
    };
    struct objectGroup{
        int height;
        object obj;
        int break_br = 0,moving_br = 0;
    };
    std::vector< std::vector<object> >Objects;
    std::vector< std::string> vari;
    std::vector< std::pair< int, std::vector<object> > > current_LV;
    int last_lv;
    bool once = 0;
    int collided;
    int break_br = 0,moving_br = 0;
    int border = 200;
    std::string cur_lv = "Level1.txt";
    Doodle *mc = nullptr;
    Brick *br = nullptr;
    Score_bar *score = nullptr;
    Platform *Plat = nullptr;
    Monster *monster = nullptr;
    MonsterGroup *monsters = nullptr;
    background *bg = nullptr;

public:
    Level();
    ~Level();

    int get_maxH(){return current_LV[last_lv-1].first;}
    int get_minH(){return current_LV[0].first;}

    void init(SDL_Renderer *renderer);
    void LevelFromFile(std::string lv_str);
    void updateLevel(SDL_Renderer *renderer);
    void LoadLevel(SDL_Renderer *renderer);
    void HandleEvent(SDL_Event event);
    void Update(SDL_Renderer *renderer);
    void Render(SDL_Renderer *renderer);
    void fix();
    void free();
};

#endif // Level_hpp
