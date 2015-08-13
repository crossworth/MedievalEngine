#ifndef MAP_H
#define MAP_H
#include "Config.h"
#include "Debugger.h"
#include "AssetsManager.h"
#include "TO.h"
#include "RenderWindow.h"
#include "Profiler.h"

namespace ME{

class Map
{
public:
    Map();
    Map(const std::string &mapName);
    void load(const std::string &mapName);
    void renderMap();
private:
    std::string mapName;
    RenderWindow *mWindow;
    AssetsManager *mAssets;
    Debugger *dbg;
};


}

#endif // MAP_H
