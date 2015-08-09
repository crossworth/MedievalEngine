#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "debugger.h"
#include "config.h"
#include "profiler.h"
#include "renderwindow.h"
#include "assetsmanager.h"
#include "luaengine.h"

/*
* Aqui definimos um ponto importante da GameEngine
* A GameEngine trabalha com gamesStates, que nada mais são do que as partes da engine
* Como tela de opções, tela do jogo, menu e tudo mais.
*
* Deve funcionar assim, criamos ou registramos um novo state e sua ordem de alguma forma
* a game engine chama a função init dele.
* Ele tem suas funções de play, pause e restart.
* Também possui funções para render, update e handleEvents
* Para fazer as transições a engine chamda onEnableTransition e onDisableTransition respectivamente.
*
*/

namespace ME{

class gameState {
public:
    gameState();
    virtual void init() = 0;
    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void restart() = 0;
    bool isRunning();
    void registerGameEngine(gameEngine *gm);
    virtual void render() = 0;
    virtual void update() = 0;
    virtual void handleEvents() = 0;
    virtual void onEnableTransition() = 0;
    virtual void onDisableTransition() = 0;
    virtual ~gameState() = 0;
protected:
    bool running;
    AssetsManager *assets;
    renderWindow *mRender;
    Event mEvent;
    gameEngine *mGameEngine;
    LuaEngine *mLua;
};

}

#endif // GAMESTATE_H
