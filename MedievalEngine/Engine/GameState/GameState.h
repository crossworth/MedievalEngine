#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "LogInc.h"
#include "Graphics/Window.h"
#include "Events/Event.h"
#include "GUI/GUI.h"

namespace ME {

class MedievalEngine;
class ResourceManager;

class GameState {
public:
    // TODO(Pedro): 
    enum Status {
        ON_ENABLE,
        ON_PLAYING,
        ON_DISABLE,
        ON_DONE
    };
public:
    GameState();
    virtual void create() = 0;
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

    GameState::Status getCurrentStatus();
protected:
    MedievalEngine* mEngine;
    ResourceManager* mResources;
    GUI mGUI;

    void setCurrentStatus(const GameState::Status& status);
    bool mIsPlaying;
    bool mIsDone;
    GameState::Status mCurrentStatus;
};

}

#endif // GAMESTATE_H
