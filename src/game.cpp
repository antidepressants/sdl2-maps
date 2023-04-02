#include "game.h"
#include "vectormap.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>

Game::Game(const char* title,int xpos,int ypos,int width,int height,bool fullScreen){
    int flags=0;
    if(fullScreen)flags=SDL_WINDOW_FULLSCREEN;
    if(SDL_Init(SDL_INIT_EVERYTHING)){
        std::cerr<<"Failed to initialize subsystems.\n";
        return;
    }
    std::cout<<"Subsystems initialized.\n";
    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if(!window){
        std::cerr<<"Failed to create window.\n";
        return;
    }
    std::cout<<"Window created.\n";
    renderer=SDL_CreateRenderer(window, -1, 0);
    if(!renderer){
        std::cerr<<"Failed to create renderer.\n";
        return;
    }
    std::cout<<"Renderer created.\n";
    isRunning=1;
}

Game::~Game(){

}

void Game::handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning=false;
            break;
        default:
            break;
    }
}

void Game::update(){}

void Game::render(Grid* grid,VectorMap** vMap,size_t count,int width,int height,int xoffset,int yoffset){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    int windowWidth,windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    double scale;
    if(grid->ncols>grid->nrows){
        scale=(double)width/grid->ncols;
    }
    else scale=(double)height/grid->nrows;
    if(scale>1)scale=(int)scale;
    if(xoffset==0)xoffset=(windowWidth-(grid->ncols*scale))/2;
    if(yoffset==0)yoffset=(windowHeight-(grid->nrows*scale))/2;
    grid->visualizeGrid(renderer,scale,xoffset,yoffset);
    for(size_t i=0;i<count;i++){
        grid->drawMap(renderer, vMap[i], scale,xoffset,yoffset);
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect rect;
    rect.x=xoffset;
    rect.y=yoffset;
    rect.w=grid->ncols*scale;
    rect.h=grid->nrows*scale;
    SDL_RenderDrawRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect left,right,top,bottom;

    left.x=0;
    right.x=xoffset+grid->ncols*scale;

    left.y=right.y=0;

    left.w=xoffset;
    right.w=windowWidth;

    left.h=right.h=windowHeight;

    top.x=bottom.x=0;

    top.y=0;
    bottom.y=yoffset+grid->nrows*scale;

    top.w=bottom.w=windowWidth;

    top.h=yoffset;
    bottom.h=windowHeight;

    SDL_RenderFillRect(renderer, &left);
    SDL_RenderFillRect(renderer, &right);
    SDL_RenderFillRect(renderer, &top);
    SDL_RenderFillRect(renderer, &bottom);

    SDL_RenderPresent(renderer);
}

void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout<<"Game cleaned.\n";
}
