#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include "rastergrid.h"
#include "vectormap.h"

class Game{
        bool isRunning=0;
        SDL_Window* window;
        SDL_Renderer* renderer;
    public:
        Game(const char* title,int xpos,int ypos,int width,int height,bool fullScreen);
        ~Game();

        void handleEvents();
        void update();
        void render(Grid*,VectorMap**,size_t,int,int,int=0,int=0);
        void clean();

        bool running(){return isRunning;};
};