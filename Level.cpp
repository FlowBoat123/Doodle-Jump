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
    bg = new background();               bg->LoadImage(renderer,"background.png");      //backgroup
    score = new Score_bar();             score->LoadImage(renderer,"top-score.png");
                                         score->LoadText(renderer,"Score : 0",{0,0,0}); // Score board and text
    background* bg = new background();   bg->LoadImage(renderer,"background.png");      // background
    mc = new Doodle();                   mc->LoadImage(renderer,"doodle.png");          // Doodle
    br = new Brick();                    br->LoadImage(renderer,"brick.png");           // brick
    Plat = new Platform();                                                              // brick group
    monsters = new MonsterGroup();                                                      // monster
    monster = new Monster();             monster->LoadImage(renderer,"FlyMonster.png"); //monster group

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
    current_LV.push_back({0,Objects[0]});
    last_lv = (int)current_LV.size();
    auto lv = current_LV[last_lv-1];

    int lv_height = lv.first;
    auto lv_object = lv.second;
    for(auto obj : lv_object){
        br = new Brick();
        br->LoadImage(renderer);
        br->setPosition(obj.x,obj.y + lv_height,0);
        Plat->add(br);
    }
}

void Level::updateLevel(SDL_Renderer *renderer)
{
    if(get_minH() > 300){
        current_LV.erase(current_LV.begin());
        once = 0;
    }
    if(!once){
        if(cur_lv == "Level1.txt"){
            current_LV.push_back({get_maxH() - 600,Objects[rand() % 2 + 1]});
            last_lv = (int)current_LV.size();
            auto lv = current_LV[last_lv-1];

            int lv_height = lv.first;
            auto lv_object = lv.second;
            break_br = rand() % 3;
            moving_br = rand() % 3;

            for(auto obj : lv_object){
                br = new Brick();
                br->LoadImage(renderer);
                obj.x = obj.x % 320;
                if(rand()%3 == 1 && moving_br > 0)
                    br->setPosition(obj.x ,obj.y + lv_height,1),moving_br--;
                else if(rand()%3 == 2 && break_br > 0)
                    br->setPosition(obj.x,obj.y + lv_height,4),break_br--;
                else br->setPosition(obj.x,obj.y + lv_height,0);
                Plat->add(br);
            }
            once = 1;
        }

    }

}

void Level::fix()
{
    if(mc->getX() == INT_MIN)mc->reset();
    if(score->getPoint() == INT_MIN)score->reset();
}

void Level::HandleEvent(SDL_Event event)
{
    mc->handleEvent(event);
}

void Level::Update(SDL_Renderer *renderer)
{
//    std::cout << mc->getX() << ' ' << mc->getY() << '\n';  //bug doodle
//    std::cout << score->getPoint() << '\n';                //bug score
    fix();
    if(score->getPoint() / 10 > 750){
        cur_lv = "Level2";
    }
    if(get_minH() > 100)updateLevel(renderer);
    collided = 0; //reset collided check
    if(mc->getY() < border){//check if doodle cross the border
        score->PassBorder();
        Plat->update(mc->vY(),renderer);
        for(auto &lv : current_LV){
            lv.first -= (mc->vY());
        }
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
    score->changeScore();
    score->LoadText(renderer,score->getString(),{0,0,0});

    if(Plat->CheckCollided( mc->getX() , mc->getY() , mc->getDoodleSprite() , mc->vY() ))collided = 1; // check doodle and plat collided
    if(monsters->CheckCollided( mc->getX() , mc->getY() , mc->vY() ))collided = 1; // check doodle and monster collided
    mc->update(collided);
}

void Level::Render(SDL_Renderer *renderer)
{
    bg->render(renderer,0,0);
    Plat->draw(renderer);
    monsters->draw(renderer); // test monster
    mc->render(renderer,mc->getX(),mc->getY(),mc->getSprite(mc->getDoodleSprite()));
    score->renderBar(renderer,0,0);
    score->renderPoint(renderer,4,0);
}

void Level::free()
{

}
