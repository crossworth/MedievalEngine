#ifndef MENUSCREEN_H
#define MENUSCREEN_H
#include "Resources/ResourceIDGenerator.h"
#include "GameState/GameState.h"
#include "Helper/Clock.h"
#include "GUI/GUI.h"

namespace ME {

class Shader;

class MenuScreen : public GameState {
public:
    MenuScreen();
    void init();
    void create();
    void onEnable(Window& window);
    void onDisable(Window& window);
    void onPlaying(Window& window);
    void update();
    void handleEvents(Event& evt);
    ~MenuScreen();
private:
    ResourceID bgID;
    ResourceID bgOptionsID;
    ResourceID logoID;

    unsigned int mFadeTime;

    TextWidgetPtr mNewGame;
    TextWidgetPtr mContinue;
    TextWidgetPtr mMultiplayer;
    TextWidgetPtr mOptions;
    TextWidgetPtr mExit;
};

}

#endif // MENUSCREEN_H
