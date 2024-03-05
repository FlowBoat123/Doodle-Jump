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

//    mc->reset();
}

void Level::test(SDL_Renderer *renderer)
{
    monster = new Monster;
    monster->SetType(1,renderer);
    br = new Brick;
    br->LoadImage(renderer);
    br->setPosition(250,500,0);
    monster->SetPosition(250,500-monster->getH()+7);
    Plat->add(br);
    monsters->add(monster);
}

void Level::LevelFromFile(std::string lv_str)
{
    Objects.clear();// clear pre memories

    std::string line; // initialize
    std::ifstream input_file(lv_str.c_str());
    std::pair<int,int>obj;

    object temp;
    std::vector <object> lv;
    std::string str;
    int cnt = 0;

    while(getline(input_file,line)){
        if(line == "--")continue;
        if(line[0] == '*'){
            Objects.push_back(lv);
            lv.clear();
            continue;
        }
        str = "";cnt = 0; //reset
        for(int i = 0;i < (int)line.size();i++){
            if(line[i] == ' '){
                if(cnt == 0)obj.first = to_int(str),cnt++;
                if(cnt == 1)obj.second = to_int(str);
                str = "";
            }
            else{
                str += line[i];
            }
        }
        if(str[0] >= '0' && str[0] <= '9')obj.second = to_int(str);
        temp.x = obj.first;
        temp.y = obj.second;
        temp.type = str;
        lv.push_back(temp);
    }
//    for(auto ob : Objects[0]){
//        std::cout << ob.x << ' ' << ob.y << ' ' << ob.type << '\n';
//    }
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
    if(get_minH() > 600){
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
        if(cur_lv == "Level2.txt"){
            current_LV.push_back({get_maxH() - 600,Objects[rand() % (int)Objects.size()]});
            last_lv = (int)current_LV.size();

            auto lv = current_LV[last_lv-1];
            int lv_height = lv.first;
            auto lv_object = lv.second;
//            std::cout << ' ' << lv_height << '\n';
            for(auto obj : lv_object){
                br = new Brick();br->LoadImage(renderer);
                monster = new Monster();
                if(obj.type == "nPlat"){
                    br->setPosition(obj.x,obj.y + lv_height,0);
                    Plat->add(br);
                }
                if(obj.type == "movingPlat"){
                    br->setPosition(obj.x,obj.y + lv_height,1);
                    Plat->add(br);
                }
                if(obj.type == "breakPlat"){
                    br->setPosition(obj.x,obj.y + lv_height,4);
                    Plat->add(br);
                }
                if(obj.type == "nMonster"){
                    monster->SetType(rand()%2,renderer);
                    monster->SetPosition(obj.x,obj.y + lv_height - (monster->getH()));
                    monsters->add(monster);
                }
                if(obj.type == "fMonster"){
                    monster->SetType(2,renderer);
                    monster->SetPosition(obj.x,obj.y + lv_height);
                    monsters->add(monster);
                }
            }
            once = 1;
        }
    }
}
void Level::HandleEvent(SDL_Event event)
{
    mc->handleEvent(event);
}

void Level::Update(SDL_Renderer *renderer)
{
    // set level
    if(score->getPoint() / 10 > 100){
        if(cur_lv != "Level2.txt"){
            cur_lv = "Level2.txt";
            LevelFromFile(cur_lv);
        }
    }
    if(get_minH() > 100)updateLevel(renderer);
    collided_br = 0; //reset collided with brick
    collided_mon = 0; // reset collided with monster

    if(mc->getY() < border){//check if doodle cross the border
        score->PassBorder();
        Plat->update(mc->vY(),renderer);
        monsters->update(mc->vY(),renderer);
        for(auto &lv : current_LV){
            lv.first -= (mc->vY());
        }
        if(mc->vY() < 0){
            score->Plus(abs(mc->vY())); // update score
        }
        mc->scroll(border); // update pos doodle
    }
//    else if(!died)Plat->animation();
    Plat->auto_update();

    if(!died){ // set animation
        monsters->animation();
        Plat->animation();
    }
    if(!score->isPassed() && mc->vY()<0){//change and update score
        score->Plus(abs(mc->vY()));
    }
    score->changeScore();                               // change score
    score->LoadText(renderer,score->getString(),{0,0,0});

    if(Plat->CheckCollided( mc->getX() , mc->getY() , mc->getDoodleSprite() , mc->vY() ))collided_br = 1;   // check doodle and plat collided
    collided_mon = monsters->CheckCollided( mc->getX() , mc->getY() , mc->vY() );                           // check collided with monster

    if(collided_mon == 2)died = 1;
//    std::cout << died << '\n';
    mc->update(collided_br | collided_mon,died);
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
