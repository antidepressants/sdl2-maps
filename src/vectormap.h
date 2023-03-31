#pragma once

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_rwops.h>
#include <map>
#include <tinyxml2.h>
#include <fstream>
#include <vector>
#include <string>
#include "color.h"
#include <unordered_map>

struct Object{
    std::string objectType;
    std::string dataType;
    double x,y; 
    std::map<std::string, std::string> tags;
    Object** nodes;
    size_t nodeNum=0;
    Object(){}
    Object(tinyxml2::XMLElement*,std::unordered_map<std::string, std::string>*);
};

struct VectorMap{
    long double minX,minY,maxX,maxY;
    std::unordered_map<unsigned long,Object> objects;
    std::unordered_map<std::string, Color>* colorProfile;
    Color defaultColor;
    VectorMap(std::string,std::unordered_map<std::string, std::string>*,std::unordered_map<std::string, Color>*,Color={0,0,0,0});
    Object* getObjectByID(unsigned long int);
    void loadNodes(tinyxml2::XMLElement*);
};