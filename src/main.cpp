#include "game.h"
#include "vectormap.h"
#include <SDL2/SDL_config.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <map>
#include <unordered_map>

int main(){
    
    std::unordered_map<std::string, Color> vectorMapColors;
    std::unordered_map<std::string, Color> theatreLevel;
    std::map<double, Color> rasterGridMap;
    std::unordered_map<std::string,std::string> uniqueKeyMap;
    
    uniqueKeyMap["primary"]=uniqueKeyMap["trunk"]=uniqueKeyMap["secondary"]=uniqueKeyMap["motorway"]=uniqueKeyMap["route"]=
    uniqueKeyMap["bridge"]=uniqueKeyMap["tunnel"]="major_road";
    uniqueKeyMap["railway"]="railway";
    uniqueKeyMap["footway"]=uniqueKeyMap["street"]=uniqueKeyMap["residential"]=uniqueKeyMap["service"]=
    uniqueKeyMap["unclassified"]=uniqueKeyMap["track"]="minor_road";

    uniqueKeyMap["building"]=uniqueKeyMap["amenity"]=uniqueKeyMap["shop"]=uniqueKeyMap["leisure"]=
    uniqueKeyMap["parking_space"]=uniqueKeyMap["office"]="building";

    uniqueKeyMap["power"]=uniqueKeyMap["gasometer"]=uniqueKeyMap["storage_tank"]="power";

    uniqueKeyMap["aeroway"]="airway";

    uniqueKeyMap["port"]=uniqueKeyMap["harbour"]="port";

    uniqueKeyMap["barrier"]="barrier";

    uniqueKeyMap["breakwater"]="breakwater";

    uniqueKeyMap["waterway"]=uniqueKeyMap["river"]=uniqueKeyMap["water"]=uniqueKeyMap["wetland"]=uniqueKeyMap["spring"]="water";

    uniqueKeyMap["industrial"]=uniqueKeyMap["crane"]=uniqueKeyMap["quarry"]=uniqueKeyMap["works"]="industrial";

    uniqueKeyMap["tree"]=uniqueKeyMap["scrub"]=uniqueKeyMap["tree_row"]=uniqueKeyMap["wood"]=
    uniqueKeyMap["village_green"]=uniqueKeyMap["forest"]="heavy_vegetation";

    uniqueKeyMap["grass"]=uniqueKeyMap["farmyard"]=uniqueKeyMap["greenfield"]=uniqueKeyMap["orchard"]="light_vegetation";

    uniqueKeyMap["brownfield"]="brownfield";

    uniqueKeyMap["cemetery"]="cemetery";

    uniqueKeyMap["boundary"]="boundary";

    uniqueKeyMap["city"]="city";

    uniqueKeyMap["village"]="village";

    vectorMapColors["major_road"]={130,0,40,255};
    vectorMapColors["minor_road"]={255,230,150,255};
    vectorMapColors["railway"]={110,0,140,255};
    vectorMapColors["heavy_vegetation"]={100,210,100,255};
    vectorMapColors["building"]={150,140,130,255};
    vectorMapColors["brownfield"]=vectorMapColors["cemetery"]={115,50,0,255};
    vectorMapColors["power"]={255,0,0,255};
    vectorMapColors["water"]={180,230,255,255};
    vectorMapColors["light_vegetation"]={150,255,150,255};
    vectorMapColors["breakwater"]=vectorMapColors["barrier"]={150,150,150,255};
    vectorMapColors["industrial"]={200,200,200,255};
    vectorMapColors["boundary"]={0,0,0,255};
    vectorMapColors["airway"]={225,150,0,255};
    vectorMapColors["port"]={0,0,255,255};

    theatreLevel["major_road"]={130,0,40,255};
    theatreLevel["railway"]={110,0,140,255};
    theatreLevel["power"]={255,0,0,255};
    theatreLevel["water"]={180,230,255,255};
    theatreLevel["industrial"]={200,200,200,255};
    theatreLevel["airway"]={225,150,0,255};
    theatreLevel["port"]={0,0,255,255};
    theatreLevel["city"]={0,0,0,255};
    theatreLevel["village"]={0,0,0,255};


    rasterGridMap[-10400]={50,150,255,255};
    rasterGridMap[-5001]={50,150,255,255};

    rasterGridMap[-5000]={70,200,255,255};
    rasterGridMap[-2001]={70,200,255,255};

    rasterGridMap[-2000]={180,230,255,255};
    rasterGridMap[0]={180,230,255,255};

    rasterGridMap[1]={255,255,255,255};
    rasterGridMap[304.8]={255,255,255,255};

    rasterGridMap[304.9]={255,210,180,255};
    rasterGridMap[609.6]={255,210,180,255};

    rasterGridMap[609.7]={255,190,150,255};
    rasterGridMap[914.4]={255,190,150,255};

    rasterGridMap[914.5]={200,180,160,255};
    rasterGridMap[1219.2]={200,180,160,255};

    rasterGridMap[1219.3]={180,160,140,255};
    rasterGridMap[1524]={180,160,140,255};

    rasterGridMap[1524.1]={160,140,120,255};
    rasterGridMap[1828.8]={160,140,120,255};

    rasterGridMap[1828.9]={140,120,100,255};
    rasterGridMap[2133.6]={140,120,100,255};

    rasterGridMap[2133.7]={120,100,80,255};
    rasterGridMap[2438.4]={120,100,80,255};

    rasterGridMap[2438.5]={120,120,100,255};
    rasterGridMap[2743.2]={120,120,100,255};

    rasterGridMap[2743.3]={120,120,120,255};
    rasterGridMap[3048]={120,120,120,255};

    rasterGridMap[3048.1]={100,100,100,255};
    rasterGridMap[3352.8]={100,100,100,255};

    rasterGridMap[3352.9]={80,80,80,255};
    rasterGridMap[3657.6]={80,80,80,255};

    rasterGridMap[3657.7]={60,60,60,255};
    rasterGridMap[5670]={60,60,60,255};

    rasterGridMap[5671]={40,40,40,255};
    rasterGridMap[6678]={40,40,40,255};

    VectorMap vMap1("data/northbeirut.osm",&uniqueKeyMap,&theatreLevel);
    VectorMap vMap2("data/southbeirut.osm",&uniqueKeyMap,&theatreLevel);
    //beirut.asc
    //tayouneh.asc
    //haret_hreik.asc

    // VectorMap vMap3("data/baabda.osm",&uniqueKeyMap,&vectorMapColors);
    //baabda.asc

    // VectorMap vMap4("data/aita_al_shaab.osm",&uniqueKeyMap,&vectorMapColors);
    //aita_al_shaab.asc

    // VectorMap vMap5("data/jabal_hmeid.osm",&uniqueKeyMap,&vectorMapColors);
    //jabal_hmeid.asc

    // VectorMap vMap6("data/idlib_outskirts.osm",&uniqueKeyMap,&vectorMapColors);
    //idlib_outskirts.asc

    // VectorMap vMap7("data/trafford_park.osm",&uniqueKeyMap,&vectorMapColors);
    //trafford_park.asc

    // VectorMap vMap8("data/lebanon.osm",&uniqueKeyMap,&theatreLevel); //big file

    VectorMap* vMaps[]={&vMap1,&vMap2};

    size_t count=sizeof(vMaps)/sizeof(VectorMap*);

    Grid grid("data/beirut.asc",&rasterGridMap);
    Game* game=new Game("Game",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1920,1080,0);
    while(game->running()){
        game->handleEvents();
        game->update();
        game->render(&grid,vMaps,count,1000,1000,1,1);
    }
    game->clean();
    return 0;
}