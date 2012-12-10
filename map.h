#ifndef MAP_H
#define MAP_H
#include "engine_config.h"
#include "debugger.h"
#include "assetsmanager.h"
#include "converter.h"
#include "renderwindow.h"
#include "profiler.h"

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
    renderWindow *mWindow;
    AssetsManager *mAssets;
    Debugger *dbg;
};


}

#endif // MAP_H
