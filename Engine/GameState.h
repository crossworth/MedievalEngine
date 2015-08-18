#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <Graphics/Window.h>
#include <LogInc.h>


namespace ME {

enum GAMESTATE_STATUS { ON_ENABLE, ON_PLAYING, ON_DISABLE, ON_DONE };

class GameState {
public:
    GameState();
    virtual void init() = 0;
    virtual void onEnable(Window &window)  = 0;
    virtual void onDisable(Window &window) = 0;
    virtual void update() = 0;
    virtual void onPlaying(Window &window) = 0;
    virtual void handleEvents(sf::Event &evt) = 0;


    void play();
    void pause();
    bool isPlaying();

    void restart();

    GAMESTATE_STATUS getCurrentStatus();

protected:
    void setCurrentStatus(const GAMESTATE_STATUS &status);

private:
    bool mIsPlaying;
    bool mIsDone;
    GAMESTATE_STATUS mCurrentStatus;

};

}

#endif // GAMESTATE_H
