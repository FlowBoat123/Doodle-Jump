#include "Level.hpp"
#include <fstream>

Level::Level()
{
    mc = nullptr;
    br = nullptr;
    score = nullptr;
    Plat = nullptr;
    monster = nullptr;
    monsters = nullptr;
}

Level::~Level()
{}

void Level::init(SDL_Renderer *renderer)
{
    score = new Score_bar();             score->LoadImage(renderer,"top-score.png");
                                         score->LoadText(renderer,"Score : 0",{0,0,0}); // Score board and text
    background* bg = new background();   bg->LoadImage(renderer,"background.png");      // background
    mc = new Doodle();                   mc->LoadImage(renderer,"doodle.png");          // Doodle
    br = new Brick();                    br->LoadImage(renderer,"brick.png");           // brick
    Plat = new Platform();                                                              // brick group
    monsters = new MonsterGroup();                                                      // monster
    monster = new Monster();             monster->LoadImage(renderer,"FlyMonster.png"); //monster group

    mc->Set(150,400);
}

void Level::LevelFromFile(std::string lv_str)
{
    Objects.clear();// clear pre memories

    std::string line; // initialize
    std::ifstream input_file(lv_str.c_str());
    std::pair<int,int>obj;

    object temp;
    std::vector <object> lv;

    while(getline(input_file,line)){
        if(line == "--")continue;
        if(line[0] == '*'){
            Objects.push_back(lv);
            lv.clear();
            continue;
        }
        int st = 0,num = 0;
        if(line[0] == 't')st = 2;
        for(int i = st;i < (int)line.size();i++){
            if(line[i] == ' '){
                obj.first = num;
                num = 0;
            }
            else{
                num = num * 10 + (line[i] - '0');
            }
        }
        if(st != 2){
            obj.second = num;
            temp.x = obj.first;
            temp.y = obj.second;
            lv.push_back(temp);
        }
        else{
            vari.push_back(std::to_string(num));
        }
    }
    input_file.close();
}

void Level::LoadLevel(SDL_Renderer* renderer)
{
    for(auto pos : Objects[0]){
        br = new Brick();
        br->LoadImage(renderer);
        br->setPosition(pos.x,pos.y);
        Plat->add(br);
    }
}

void Level::HandleEvent(SDL_Event event)
{
    mc->handleEvent(event);
}

void Level::Update(SDL_Renderer *renderer)
{
//    Doodle_Width = 58,Height = 57 | Doodle and brick inform | Brick_width = 70,height = 20;
    collided = 0;
    if(mc->getY() < border){//check if doodle cross the border
        score->PassBorder();
        Plat->update(mc->vY(),renderer);
        if(mc->vY() < 0){
            score->Plus(abs(mc->vY())); // update score
        }
        mc->scroll(border); // update pos doodle
    }
    else Plat->animation();
    Plat->auto_update();

    monsters->animation();


    if(!score->isPassed() && mc->vY()<0){//change and update score
        score->Plus(abs(mc->vY()));
    }
    score->changeScore(score->getPoint());
    score->LoadText(renderer,score->getString(),{0,0,0});

    if(Plat->CheckCollided( mc->getX() , mc->getY() , mc->getDoodleSprite() , mc->vY() ))collided = 1; // check doodle and plat collided
    if(monsters->CheckCollided( mc->getX() , mc->getY() , mc->vY() ))collided = 1; // check doodle and monster collided
    mc->update(collided);
}

void Level::Render(SDL_Renderer *renderer)
{
//    bg->render(renderer,0,0);
    Plat->draw(renderer);
//    monsters->draw(renderer); // test monster
    mc->render(renderer,mc->getX(),mc->getY(),mc->getSprite(mc->getDoodleSprite()));
//    score->renderBar(renderer,0,0);
//    score->renderPoint(renderer,4,0);
}
