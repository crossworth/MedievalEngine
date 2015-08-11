#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "debugger.h"
#include "renderwindow.h"
#include "profiler.h"
#include "assetsmanager.h"
#include "config.h"
#include "gamestate.h"
#include "TO.h"
#include "cfgparser.h"


namespace ME {

class gameState;

class gameEngine {
public:
    static gameEngine* getInstance(int argc = 0, char **argv = nullptr);
    void init();
    void run();
    void clear();
    static void changeGameState(const std::string &name);

    int onExit();
    gameState *getActiveGameState();
    ~gameEngine();
protected:
    int returnCode;
private:
    static gameEngine *gm;
    gameEngine(int argc, char **argv);
    Debugger *dbg;
    std::string gameStateEnable;
    std::map<std::string, gameState*> mGamesStates;
    AssetsManager *assets;
    renderWindow *mWindow;
    bool _startedMainLoop;
};

}

#endif // GAMEENGINE_H
