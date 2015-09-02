#ifndef MENUSCREEN_H
#define MENUSCREEN_H
#include "Resources/ResourceIDGenerator.h"
#include "GameState/GameState.h"
#include "Helper/Clock.h"
#include "GUI/GUI.h"

namespace ME {

class MenuScreen : public GameState {
public:
    MenuScreen(MedievalEngine* engine);
    void init();
    void onEnable(Window& window);
    void onDisable(Window& window);
    void onPlaying(Window& window);
    void update();
    void handleEvents(Event& evt);
    ~MenuScreen();
private:
    ResourceID sceneBackgroundID;
    ResourceID backgroundOptionsID;
    ResourceID logoID;

    unsigned int mFadeTime;


    TextWidget* mNewGame;
    TextWidget* mContinue;
    TextWidget* mMultiplayer;
    TextWidget* mOptions;
    TextWidget* mExit;
};

}

#endif // MENUSCREEN_H
