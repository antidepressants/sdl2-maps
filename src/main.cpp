#include "game.h"
#include "vectormap.h"
#include <SDL2/SDL_config.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <map>

int main(){
    
    std::map<std::string, Color> vectorMapColors;
    std::map<double, Color> rasterGridMap;
    std::map<std::string,std::string> uniqueKeyMap;
    
    uniqueKeyMap["highway"]=uniqueKeyMap["railway"]=uniqueKeyMap["bridge"]=uniqueKeyMap["tunnel"]=
    uniqueKeyMap["footway"]=uniqueKeyMap["route"]=uniqueKeyMap["street"]="road";

    uniqueKeyMap["building"]=uniqueKeyMap["amenity"]=uniqueKeyMap["shop"]=uniqueKeyMap["leisure"]=
    uniqueKeyMap["parking_space"]=uniqueKeyMap["office"]="building";

    uniqueKeyMap["power"]=uniqueKeyMap["gasometer"]=uniqueKeyMap["storage_tank"]="power";

    uniqueKeyMap["barrier"]="barrier";

    uniqueKeyMap["breakwater"]="breakwater";

    uniqueKeyMap["waterway"]=uniqueKeyMap["river"]=uniqueKeyMap["water"]="water";

    uniqueKeyMap["industrial"]=uniqueKeyMap["crane"]="industrial";

    uniqueKeyMap["tree"]=uniqueKeyMap["scrub"]=uniqueKeyMap["tree_row"]=uniqueKeyMap["wood"]=
    uniqueKeyMap["village_green"]=uniqueKeyMap["forest"]="heavy_vegetation";

    uniqueKeyMap["grass"]=uniqueKeyMap["farmyard"]=uniqueKeyMap["greenfield"]="light_vegetation";

    uniqueKeyMap["brownfield"]="brownfield";

    uniqueKeyMap["cemetery"]="cemetery";

    uniqueKeyMap["boundary"]="boundary";

    uniqueKeyMap["city"]="city";

    vectorMapColors["road"]={255,0,200,255};
    vectorMapColors["heavy_vegetation"]={0,255,0,255};
    vectorMapColors["building"]={200,0,255,255};
    vectorMapColors["brownfield"]=vectorMapColors["cemetery"]={115,50,0,255};
    vectorMapColors["power"]={255,0,0,255};
    vectorMapColors["water"]={180,230,255,255};
    vectorMapColors["light_vegetation"]={150,255,150,255};
    vectorMapColors["breakwater"]=vectorMapColors["barrier"]={150,150,150,255};
    vectorMapColors["industrial"]={200,200,200,255};
    vectorMapColors["boundary"]=vectorMapColors["city"]={0,0,0,255};

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

    // VectorMap vMap1("data/beirut.osm",&uniqueKeyMap,&vectorMapColors);
    // VectorMap vMap2("data/haret_hreik.osm",&uniqueKeyMap,&vectorMapColors);
    VectorMap vMap3("data/tayouneh.osm",&uniqueKeyMap,&vectorMapColors);
    //tayouneh.asc
    // VectorMap vMap4("data/port.osm",&uniqueKeyMap,&vectorMapColors);
    // VectorMap vMap5("data/beirut2.osm",&uniqueKeyMap,&vectorMapColors);
    // VectorMap vMap6("data/beirut3.osm",&uniqueKeyMap,&vectorMapColors);
    //beirut.asc

    // VectorMap vMap7("data/baabda.osm",&uniqueKeyMap,&vectorMapColors);
    //baabda.asc

    // VectorMap vMap8("data/aita_al_shaab.osm",&uniqueKeyMap,&vectorMapColors);
    // VectorMap vMap9("data/jabal_hmeid.osm",&uniqueKeyMap,&vectorMapColors);
    //jabal_hmeid.asc

    // VectorMap vMap10("data/beirutblock.osm",&uniqueKeyMap,&vectorMapColors);
    //beirut2.asc

    // VectorMap vMap11("data/idlib_outskirts.osm",&uniqueKeyMap,&vectorMapColors);
    //idlib_outskirts.asc

    // VectorMap vMap12("data/trafford_park.osm",&uniqueKeyMap,&vectorMapColors);
    //trafford_park.asc

    // VectorMap vMaps[]={};

    VectorMap* vMaps[]={&vMap3};

    size_t count=sizeof(vMaps)/sizeof(VectorMap*);

    Grid grid("data/tayouneh.asc",&rasterGridMap);
    Game* game=new Game("Game",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1920,1080,0);
    while(game->running()){
        game->handleEvents();
        game->update();
        game->render(&grid,vMaps,count,1000,800);
    }
    game->clean();
    return 0;
}