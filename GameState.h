#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "Debugger.h"
#include "Config.h"
#include "Profiler.h"
#include "RenderWindow.h"
#include "AssetsManager.h"
#include "LuaEngine.h"
#include "GameEngine.h"
#include "Effects.h"
#include "CallBack.h"

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


class GameState {
public:
    GameState();
    virtual void init() = 0;
    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void restart() = 0;
    bool isRunning();
    void registerGameEngine(GameEngine *gm);
    virtual void render() = 0;
    virtual void update() = 0;
    virtual void handleEvents() = 0;
    virtual void onEnableTransition() = 0;
    virtual void onDisableTransition() = 0;
    virtual ~GameState() = 0;


    GAME_STATE getState();
    std::string getStateString();
    void setState(const GAME_STATE &state);
    void setState(const std::string &state);

    float getTime();
    void restartTime();

    void addEffect(Effects *effect);
    void addCallBack(CallBack *callBack);

protected:
    bool running;
    std::vector<Effects*> mEffects;
    std::vector<CallBack*> mCallBacks;
    AssetsManager *assets;
    RenderWindow *mRender;
    Event mEvent;
    GameEngine *mGameEngine;
    LuaEngine *mLua;
    sf::Clock mClock;
    GAME_STATE mState;
};

}

#endif // GAMESTATE_H
