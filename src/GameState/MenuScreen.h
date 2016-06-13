#ifndef MENUSCREEN_H
#define MENUSCREEN_H
#include "GameState/GameState.h"


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
    std::string bgName;
    std::string bgOptionsName;
    std::string logoName;

    Shader* shader;

    unsigned int mFadeTime;

    TextWidgetPtr mNewGame;
    TextWidgetPtr mContinue;
    TextWidgetPtr mMultiplayer;
    TextWidgetPtr mOptions;
    TextWidgetPtr mExit;
};

}

#endif // MENUSCREEN_H
