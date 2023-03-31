#include "rastergrid.h"
#include "vectormap.h"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
std::ifstream fin;
std::ofstream fout;

Grid::Grid(std::string fileName,std::map<double, Color>* pCp,Color defCol){
    defaultColor=defCol;
    colorProfile=pCp;
    fin.open(fileName);
    std::string line;
    fin >> line >> line;
    ncols = std::stoi(line);
    fin >> line >> line;
    nrows = std::stoi(line);
    fin >> line >> line;
    xllcorner = std::stold(line);
    fin >> line >> line;
    yllcorner = std::stold(line);
    fin >> line >> line;
    cellsize = std::stold(line);
    fin >> line >> line;
    nodata_value = std::stold(line);
    xurcorner=xllcorner+ncols*cellsize;
    yurcorner=yllcorner+nrows*cellsize;

    maxValue=minValue=nodata_value;
    cells=new double[nrows*ncols];
    for(size_t i=0;i<nrows;i++){
        for(size_t j=0;j<ncols;j++){
            fin>>line;
            cells[i*ncols+j]=std::stol(line);
            double data=cells[i*ncols+j];
            if(maxValue<data)maxValue=data;
            if(minValue>data)minValue=data;
        }
    }
    fin.close();
}

void Grid::visualizeGrid(SDL_Renderer* renderer,double scale,int xoffset,int yoffset,double minX,double minY,double maxX,double maxY){
    if(!(minX or minY or maxX or maxY)){
        minX=xllcorner;
        minY=yllcorner;
        maxX=xurcorner;
        maxY=yurcorner;
    }

    int i0=(yurcorner-maxY)/cellsize;
    int iN=(yurcorner-minY)/cellsize;
    int j0=(minX-xllcorner)/cellsize;
    int jN=(maxX-xllcorner)/cellsize;

    for(size_t i=i0;i<=iN;i++){
        for(size_t j=j0;j<=jN;j++){
            long double data=cells[i*ncols+j];
            int r,g,b,a;
            
            auto it=colorProfile->begin();
            while(it!=colorProfile->end() and std::next(it)->first<data){
                it++;
            }

            if(std::next(it)!=colorProfile->end() and it->first<=data){
                auto lowerBound=(it);
                auto higherBound=std::next(lowerBound);
                double dataDifference=data-lowerBound->first;
                double mapDifference=higherBound->first-lowerBound->first;
                double ratio=dataDifference/mapDifference;
                r=(lowerBound->second.r-lowerBound->second.r*ratio)+(higherBound->second.r*ratio);
                g=(lowerBound->second.g-lowerBound->second.g*ratio)+(higherBound->second.g*ratio);
                b=(lowerBound->second.b-lowerBound->second.b*ratio)+(higherBound->second.b*ratio);
                a=(lowerBound->second.a-lowerBound->second.a*ratio)+(higherBound->second.a*ratio);
            }

            else{
                r=defaultColor.r;
                g=defaultColor.g;
                b=defaultColor.b;
                a=defaultColor.a;
            }
            SDL_SetRenderDrawColor(renderer, r, g, b, a);
            SDL_Rect rect;
            rect.x=(j-j0)*scale+xoffset;
            rect.y=(i-i0)*scale+yoffset;
            rect.h=(scale<1)?1:scale;
            rect.w=(scale<1)?1:scale;
            SDL_RenderFillRect(renderer, &rect);
            //SDL_RenderDrawRect(renderer, &rect);
        }
    }
}

void Grid::drawRectAtCoordinate(SDL_Renderer* renderer,double scale,double minX,double minY,double maxX,double maxY,int xoffset,int yoffset){
    SDL_Rect rect;
    rect.x=((minX-xllcorner)/cellsize)*scale+xoffset;
    rect.y=((yurcorner-maxY)/cellsize)*scale+yoffset;
    rect.h=((maxY-minY)/cellsize)*scale;
    rect.w=((maxX-minX)/cellsize)*scale;
    SDL_RenderDrawRect(renderer, &rect);
}

void Grid::drawPath(SDL_Renderer* renderer, double scale, Object object,int xoffset,int yoffset){
    SDL_Point* points=new SDL_Point[object.nodeNum];
    for(size_t i=0;i<object.nodeNum;i++){
        points[i]={int(((object.nodes[i]->x-xllcorner)/cellsize)*scale)+xoffset,int(((yurcorner-object.nodes[i]->y)/cellsize)*scale)+yoffset};
    }
    SDL_RenderDrawLines(renderer, points, object.nodeNum);
}

void Grid::drawMap(SDL_Renderer* renderer, VectorMap* vMap, double scale,int xoffset,int yoffset){
    Color color;

    for(auto object:vMap->objects){
        color.r=vMap->defaultColor.r;
        color.g=vMap->defaultColor.g;
        color.b=vMap->defaultColor.b;
        color.a=vMap->defaultColor.a;

        auto *colorMap=vMap->colorProfile;

        if(colorMap->find(object.dataType)!=colorMap->end()){
            color.r=(*colorMap)[object.dataType].r;
            color.g=(*colorMap)[object.dataType].g;
            color.b=(*colorMap)[object.dataType].b;
            color.a=(*colorMap)[object.dataType].a;
        }else continue;

        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        if(object.objectType=="node") drawRectAtCoordinate(renderer, scale, object.x, object.y, object.x, object.y,xoffset,yoffset);
        if(object.objectType=="way") drawPath(renderer, scale, object,xoffset,yoffset);
    }
}