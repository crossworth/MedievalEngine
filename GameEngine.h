#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "Log.h"
#include "RenderWindow.h"
#include "Profiler.h"
#include "AssetsManager.h"
#include "Config.h"
#include "GameState.h"
#include "TO.h"
#include "CFGParser.h"


namespace ME {

class GameState;

class GameEngine {
public:
    static GameEngine* getInstance(int argc = 0, char **argv = nullptr);
    void init();
    void run();
    void clear();
    static void changeGameState(const std::string &name);

    int onExit();
    GameState *getActiveGameState();
    ~GameEngine();
protected:
    int returnCode;
private:
    static GameEngine *gm;
    GameEngine(int argc, char **argv);
    Debugger *dbg;
    std::string gameStateEnable;
    std::map<std::string, GameState*> mGamesStates;
    AssetsManager *assets;
    RenderWindow *mWindow;
    bool _startedMainLoop;
};

}

#endif // GAMEENGINE_H
