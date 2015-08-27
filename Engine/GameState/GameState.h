#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "LogInc.h"
#include "Graphics/Window.h"
#include "Events/Event.h"


namespace ME {

class MedievalEngine;

class GameState {
public:
    enum GAME_STATUS {ON_ENABLE, ON_PLAYING, ON_DISABLE, ON_DONE};
public:
    GameState();
    virtual void init() = 0;
    virtual void onEnable(Window& window)  = 0;
    virtual void onDisable(Window& window) = 0;
    virtual void update() = 0;
    virtual void onPlaying(Window& window) = 0;
    virtual void handleEvents(Event& evt) = 0;

    void registerEngine(MedievalEngine* engine);

    void play();
    void pause();
    bool isPlaying();

    void restart();

    GAME_STATUS getCurrentStatus();
protected:
    MedievalEngine* mEngine;
    void setCurrentStatus(const GameState::GAME_STATUS& status);
    bool mIsPlaying;
    bool mIsDone;
    GameState::GAME_STATUS mCurrentStatus;
};

}

#endif // GAMESTATE_H
