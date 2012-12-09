#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "debugger.h"
#include "renderwindow.h"
#include "profiler.h"
#include "assetsmanager.h"
#include "lua.h"
#include "engine_config.h"
#include "gamestate.h"
#include "converter.h"
#include "cfgparser.h"
#include "mainstate.h"
#include "luafunctions.h"


namespace ME{

class gameEngine
{
public:
    static gameEngine* getInstance();
    void init();
    void run();
    void clear();
    void changeGameState(const std::string &name);
    gameState *getGameStateEnable();
    ~gameEngine();
private:
    gameEngine();
    Debugger *dbg;
    std::string gameStateEnable;
    std::map<std::string,gameState*> mGamesStates;
    AssetsManager *assets;
    renderWindow *mWindow;
};

}

#endif // GAMEENGINE_H
