#pragma once

#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <string>
#include <vector>
#include "vectormap.h"

struct Grid{
        unsigned int ncols,nrows;
        long double xllcorner,yllcorner,xurcorner,yurcorner;
        long double cellsize,nodata_value,maxValue,minValue;
        std::map<double, Color>* colorProfile;
        double* cells;
        Color defaultColor;
    public:
        Grid(std::string fileName,std::map<double, Color>*,Color={0,0,0,255});
        void exportCoordsToCSV(std::string fileName);
        void visualizeGrid(SDL_Renderer*,double scale,int xoffset,int yoffset,double minX=0,double minY=0,double maxX=0,double maxY=0);
        void drawRectAtCoordinate(SDL_Renderer*,double,double,double,double,double,int,int);
        void drawPath(SDL_Renderer*,double,Object,int,int);
        void drawMap(SDL_Renderer*,VectorMap*,double,int,int);
};