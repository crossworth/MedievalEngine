#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "debugger.h"
#include "engine_config.h"
#include "profiler.h"
#include "renderwindow.h"
#include "assetsmanager.h"
#include "lua.h"

namespace ME{

class gameState
{
public:
    gameState();
    virtual void init()=0;
    virtual void play()=0;
    virtual void pause()=0;
    bool isRunning();
    void registerGameEngine(gameEngine *gm);
    virtual void render()=0;
    virtual void update()=0;
    virtual void handleEvents() =0;
    virtual ~gameState()=0;
protected:
    bool running;
    AssetsManager *assets;
    renderWindow *mRender;
    Event mEvent;
    gameEngine * mGameEngine;
    Lua *mLua;
};

}

#endif // GAMESTATE_H
