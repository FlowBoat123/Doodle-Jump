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
    struct object{
        int x,y;
        std::string type = "";
    };
    std::vector< std::vector<object> >Objects;
    std::vector< std::string> vari;
    std::vector< std::pair< int, std::vector<object>> > current_LV;
    int collided;
    int border = 200;
    Doodle *mc = nullptr;
    Brick *br = nullptr;
    Score_bar *score = nullptr;
    Platform *Plat = nullptr;
    Monster *monster = nullptr;
    MonsterGroup *monsters = nullptr;

public:
    Level();
    ~Level();
    void init(SDL_Renderer *renderer);
    void LevelFromFile(std::string lv_str);
    void LoadLevel(SDL_Renderer *renderer);
    void HandleEvent(SDL_Event event);
    void Update(SDL_Renderer *renderer);
    void Render(SDL_Renderer *renderer);
};

#endif // Level_hpp
