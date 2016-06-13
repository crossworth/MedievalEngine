#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "GUI/GUI.h"
#include "Effects/Fade.h"
#include "Effects/Strobe.h"
#include "Effects/Shader.h"


namespace ME {

class MedievalEngine;
class ResourceManager;

class GameState {
public:
    /**
     * The ME::GameState::Status enum
     */
    enum Status {
        ON_ENABLE,  ///< GameState on enable status
        ON_PLAYING, ///< GameState on playing status
        ON_DISABLE ///< GameState on disable status
    };
public:
    GameState();
    virtual ~GameState();

    virtual void create() = 0;
    virtual void init() = 0;
    virtual void onEnable(Window& window)  = 0;
    virtual void onDisable(Window& window) = 0;
    virtual void onPlaying(Window& window) = 0;
    virtual void update() = 0;
    virtual void handleEvents(Event& evt) = 0;

    void registerEngine(MedievalEngine* engine);

    void play();
    void pause();
    bool isPlaying();

    void restart();

    GameState::Status getCurrentStatus();
protected:
    void setCurrentStatus(const GameState::Status& status);

    MedievalEngine* mEngine;
    GameState::Status mCurrentStatus;
    GUI mGUI;
    bool mIsPlaying;
};

}

#endif // GAMESTATE_H
