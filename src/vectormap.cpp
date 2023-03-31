#include "vectormap.h"
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <tinyxml2.h>
#include <unordered_map>

Object::Object(tinyxml2::XMLElement* element,std::unordered_map<std::string, std::string>* uniqueKeyMapPtr){
    objectType=element->Name();
    for(tinyxml2::XMLElement* tag=element->FirstChildElement("tag");tag!=nullptr;tag=tag->NextSiblingElement("tag")){
            if(uniqueKeyMapPtr->find(tag->Attribute("k"))!=uniqueKeyMapPtr->end()){
                dataType=(*uniqueKeyMapPtr)[tag->Attribute("k")];
                break;
            }
            else if(uniqueKeyMapPtr->find(tag->Attribute("v"))!=uniqueKeyMapPtr->end()){
                dataType=(*uniqueKeyMapPtr)[tag->Attribute("v")];
                break;
            }
    }
    for(tinyxml2::XMLElement* node=element->FirstChildElement("nd");node!=nullptr;node=node->NextSiblingElement("nd"))nodeNum++;
    nodes=new Object*[nodeNum];
    if (objectType=="node"){
        x=std::stod(element->Attribute("lon"));
        y=std::stod(element->Attribute("lat"));
    }
}

Object* VectorMap::getObjectByID(unsigned long int uid){
    if (objects.find(uid)==objects.end())return nullptr;
    return &objects[uid];
}

VectorMap::VectorMap(std::string file,std::unordered_map<std::string, std::string>* uniqueKeyMapPtr,std::unordered_map<std::string, Color>* colorProfilePtr,Color defCol){
    colorProfile=colorProfilePtr;
    defaultColor=defCol;
    tinyxml2::XMLDocument document;
    tinyxml2::XMLError eResult=document.LoadFile(file.c_str());
    tinyxml2::XMLNode* root=document.RootElement();
    tinyxml2::XMLElement* currentElement=root->FirstChildElement();
    for(tinyxml2::XMLElement* currentElement=root->FirstChildElement();currentElement!=nullptr;currentElement=currentElement->NextSiblingElement()){
        if(!std::strcmp(currentElement->Name(),"bounds")){
            minX=std::stol(currentElement->Attribute("minlon"));
            minY=std::stol(currentElement->Attribute("minlat"));
            maxX=std::stol(currentElement->Attribute("maxlon"));
            maxY=std::stol(currentElement->Attribute("maxlat"));
            continue;
        }
    }
    while(currentElement->NextSiblingElement()!=nullptr){
        currentElement=currentElement->NextSiblingElement();
        Object object(currentElement,uniqueKeyMapPtr);
        if(object.objectType=="way"){
            size_t i=0;
            for(tinyxml2::XMLElement* node=currentElement->FirstChildElement("nd");node!=nullptr;node=node->NextSiblingElement("nd")){
                Object* nodePointer=getObjectByID(std::stoul(node->Attribute("ref")));
                if(nodePointer!=nullptr) object.nodes[i++]=nodePointer;
            }
        }
        objects[std::stoul(currentElement->Attribute("id"))]=object;
        if(object.objectType=="relation"){
            for(tinyxml2::XMLElement* member=currentElement->FirstChildElement("member");member!=nullptr;member=member->NextSiblingElement("member")){
                Object* memberPointer=getObjectByID(std::stoul(member->Attribute("ref")));
                if(memberPointer!=nullptr)
                    if(colorProfile->find(memberPointer->dataType)==colorProfile->end())
                        memberPointer->dataType=object.dataType;
            }
        }
    }
}