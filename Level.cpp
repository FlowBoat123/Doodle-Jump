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
{
    delete mc;
    delete score;
    delete monster;
    delete monsters;
    delete bg;
    delete dark_bg;
    delete fl;
    delete fly_gr;
    delete pause_bt;
//    delete br;
//    delete plat;
}

void Level::init(SDL_Renderer *renderer)
{
    bg = new background();               bg->LoadImage(renderer);      //backgroup
    dark_bg = new darkbg();              dark_bg->LoadImage(renderer);
    score = new Score_bar();             score->LoadImage(renderer,"top-score.png");
                                         score->LoadText(renderer,"Score : 0",{0,0,0}); // Score board and text
    mc = new Doodle();                   mc->LoadImage(renderer,"template/doodle.png");          // Doodle
    br = new Brick();                    br->LoadImage(renderer,"brick.png");           // brick
    Plat = new Platform();                                                              // brick group
    monsters = new MonsterGroup();                                                      // monster
    monster = new Monster();             monster->LoadImage(renderer,"FlyMonster.png"); //monster group

    fl = new FlyThings();
    fly_gr = new FlyGroup();

    pause_bt = new Button();
    pause_bt->SetPosition(370,0);pause_bt->SetType(-1);
    pause_bt->LoadImage(renderer);
}

void Level::test(SDL_Renderer *renderer)
{
    monster = new Monster;

    br = new Brick;
    br->LoadImage(renderer);
    br->setPosition(250,450,0);
    Plat->add(br);

    fl = new FlyThings;
    fl->SetType(2);
    fl->SetPosition(br->getX() + (br->getW() / 2 - fl->getW() / 2),br->getY() - fl->getH() + 5);
    fl->LoadImage(renderer);

    fly_gr->add(fl);
//    monster->SetType(1,renderer);
//    monster->SetPosition(250,500-monster->getH()+7);
//    monsters->add(monster);
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
    input_file.close();
}

void Level::MakeLevel(SDL_Renderer *renderer)
{
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

void Level::LoadLevel(SDL_Renderer* renderer)
{
    current_LV.push_back({0,Objects[0]});
    MakeLevel(renderer);
    current_LV.push_back({-600,Objects[1]});
    MakeLevel(renderer);
}

void Level::genFly(int t,SDL_Renderer *renderer,Brick *br)
{
    fl = new FlyThings;
    fl->SetType(t);fl->LoadImage(renderer);
    fl->SetPosition(br->getX() + (br->getW() / 2 - fl->getW() / 2),br->getY() - fl->getH() + 5);
    fly_gr->add(fl);
}

void Level::genBrick(SDL_Renderer *renderer,int x,int y,int t)
{
    br = new Brick();br->LoadImage(renderer);
    br->setPosition(x,y,t);
    Plat->add(br);
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

            break_br = rand() % 6;
            moving_br = rand() % 3;
            fly_sprite = rand() % 2;
            springs = rand() % 3;

            for(auto obj : lv_object){
                br = new Brick();
                br->LoadImage(renderer);
                obj.x = obj.x % 320;
                if(rand()%3 == 1 && moving_br)
                    br->setPosition(obj.x ,obj.y + lv_height,1),moving_br--;
                else if(rand()%3 == 2 && break_br)
                    br->setPosition(obj.x,obj.y + lv_height,4),break_br--;
                else if(rand() % 7 == 0 && springs){
                    br->setPosition(obj.x,obj.y + lv_height,0);
                    genFly(1,renderer,br);
                    springs--;
                }
                else if(rand() % 10 == 0 && fly_sprite){
                    br->setPosition(obj.x,obj.y + lv_height,0);
                    fly_type = rand() % 2;if(fly_type == 1)fly_type++;
                    genFly(fly_type,renderer,br);
                    fly_sprite--;
                }
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
                    if(rand() % 20 == 0){
                        fly_type = rand() % 2;if(fly_type == 1)fly_type++;
                        genFly(fly_type,renderer,br);
                    }
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
                    monster_type = rand() % 2;
                    monster->SetType(monster_type,renderer);
                    monster->SetPosition(obj.x,obj.y + lv_height - (monster->getH()));
                    monsters->add(monster);
                    if(monster_type){
                        monster->SetPosition(obj.x + 8,obj.y + lv_height - (monster->getH()));
                        genBrick(renderer,obj.x - 20,obj.y + lv_height,0);
                        genBrick(renderer,obj.x + br->getW() - 22,obj.y + lv_height,0);
                    }
                    else{
                        genBrick(renderer,obj.x,obj.y + lv_height,0);
                    }
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

void Level::HandleEvent(SDL_Event *event)
{
    if(died)return;
    mc->handleEvent(event);
    if(event->type == SDL_MOUSEBUTTONDOWN)
        if(pause_bt->handleEvent(event))pause = 1;
    if(event->type == SDL_KEYDOWN)
        if(event->key.keysym.sym == SDLK_SPACE)pause = 1;
}

bool Level::change_bg()
{
        if(dark_mode){
            if(score->getPoint()/10 - lastPoint >= 500){
                lastPoint = score->getPoint() / 10;
                return true;
            }
        }
        else{
            if(score->getPoint()/10 - lastPoint >= 1000){
                lastPoint = score->getPoint() / 10;
                return true;
            }
        }
        return false;
}

void Level::updateBG(SDL_Renderer *renderer)
{
    if(change_bg()){
        if(dark_mode) dark_mode = 0;
        else dark_mode = 1;
        bg->changeBG(renderer);
    }
}

void Level::Update(SDL_Renderer *renderer)
{
    // set level
//    /*
    if(score->getPoint() / 10 > 100){
        if(cur_lv != "Level2.txt"){
            cur_lv = "Level2.txt";
            LevelFromFile(cur_lv);
        }
    }
    if(get_minH() > 400)updateLevel(renderer);
//    */

    if(died && outScreen){
        mc->endSelf();
        if(!mc->isDied()){
            Plat->endSelf();
            monsters->endSelf(); // die feature
            fly_gr->endSelf();
            bg->animation();
        }
        return;
    }

    if(mc->getY() > 700){
        mc->SetTimeFall();
        outScreen = 1;died = 1;
    }
    collided_br = 0; //reset collided with brick
    collided_mon = 0; // reset collided with monster

    if(mc->getY() < border){//check if doodle cross the border
        score->PassBorder();
        Plat->update(mc->vY(),renderer);
        monsters->update(mc->vY(),renderer);
        fly_gr->update(mc->vY(),renderer);
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
    collided_fly_sprite = fly_gr->CheckCollided( mc->getX() , mc->getY() , mc->getDoodleSprite() , mc->vY() );

    if(collided_mon == 2 && !mc->isFlying())died = 1;

    if(collided_fly_sprite == 1){
        fly_gr->preAnimation();
        mc->SetFly(fly_gr->getType()); // fly

    }
    if(mc->isFlying()){
        mc->animation();    // cancel fly
        fly_gr->animation(mc->getX(),mc->getY(),mc->getDirection());//animation fly
    }
    else{
        fly_gr->destroy_sprite();
    }
    mc->update(collided_br | collided_mon,died); // update collided
    updateBG(renderer);                          // update background
}

void Level::Render(SDL_Renderer *renderer)
{
    bg->render(renderer);
    Plat->draw(renderer);
    monsters->draw(renderer); // test monster
    mc->render(renderer,mc->getX(),mc->getY(),mc->getSprite(mc->getDoodleSprite()));
    fly_gr->draw(renderer,mc->getDirection());

    if(dark_mode)dark_bg->render(renderer,mc->getX(),mc->getY());

    score->renderBar(renderer,0,0);
    score->renderPoint(renderer,4,0);
    pause_bt->Render(renderer);
}

void Level::reset()
{
    died = 0;
    mc->SetPosition(150,400);
}

void Level::free()
{

}
