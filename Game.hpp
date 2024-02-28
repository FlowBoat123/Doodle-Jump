#ifndef Game_hpp
#define Game_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>


class Game{

    private:
        int ct = 0;
        bool isRunning;
        SDL_Window *window;
        SDL_Renderer *renderer;

    public:
        Game();
        ~Game();
        bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
        void update();
        void handleEvents();
        void render();
        void clean();
        bool running(){return isRunning;}

        static Game& getInstance();

        SDL_Renderer* getRenderer() const {
            return renderer;
        }
};

#endif // Game_hpp


