#ifndef Score_hpp
#define Score_hpp

#include "Game.hpp"

class Score_bar{
    public:
        Score_bar();
        bool LoadText(SDL_Renderer *renderer,std::string path,SDL_Color textColor);
        bool LoadImage(SDL_Renderer *renderer,std::string path);
        void free();

        void renderBar(SDL_Renderer *renderer,int x,int y, SDL_Rect *clip = NULL);
        void renderPoint(SDL_Renderer *renderer,int x,int y, SDL_Rect *clip = NULL);
        void Plus(int x = 0);
        void reset(){Point = 0;}

        void PassBorder(){under_h = 1;}
        bool isPassed(){return under_h;}
        int getPoint(){return Point;}
        int getwidth(){return mwidth;}
        int getheight(){return mheight;}
        std::string getString(){return Score_text;}
        void changeScore(){
            Score_text = "Score : " + std::to_string(Point/10);
        }

    private:
        SDL_Texture *mTexture,*gTexture;
        TTF_Font *gFont;
        int mwidth,mheight,gwidth,gheight;
        int Point;
        bool under_h;
        std::string Score_text;
        SDL_Color textCO = {0,0,0};
};
#endif // Score_hpp
