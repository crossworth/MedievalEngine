#ifndef MENUSCREEN_H
#define MENUSCREEN_H
#include "Resources/ResourceIDGenerator.h"
#include "GameState/GameState.h"
#include "Helper/Clock.h"

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
private:
    ResourceID sceneBackgroundID;
    ResourceID backgroundOptionsID;
    ResourceID logoID;
    ResourceID optNewGameID;
    ResourceID optContinueID;
    ResourceID optMultiplayerID;
    ResourceID optOptionsID;
    ResourceID optExitID;
};

}

#endif // MENUSCREEN_H
