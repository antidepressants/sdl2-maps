#include <map>

struct Color{
    unsigned int r,g,b,a;
    Color(){}
    Color(unsigned int,unsigned int,unsigned int,unsigned int);
};

struct ColorProfile{
    std::map<double, Color> colorMap;
    ColorProfile(double[],Color[]);
};