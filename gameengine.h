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
#include "editor.h"


namespace ME{

class gameEngine
{
public:
    static gameEngine* getInstance(int argc = 0,char **argv = nullptr);
    void init();
    void run();
    void clear();
    void changeGameState(const std::string &name);
    int onExit();
    gameState *getGameStateEnable();
    ~gameEngine();
protected:
    int returnCode;
private:
    gameEngine(int argc,char **argv);
    Debugger *dbg;
    std::string gameStateEnable;
    std::map<std::string,gameState*> mGamesStates;
    AssetsManager *assets;
    renderWindow *mWindow;
    editor *mEditor;
};

}

#endif // GAMEENGINE_H
