#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H
#include "Resources/ResourceIDGenerator.h"
#include "GameState/GameState.h"
#include "Helper/Clock.h"

namespace ME {

class LoadingScreen : public GameState {
public:
    LoadingScreen(MedievalEngine* engine);
    void init();
    void onEnable(Window& window);
    void onDisable(Window& window);
    void onPlaying(Window& window);
    void update();
    void handleEvents(Event& evt);
private:
    ResourceID sceneBackgroundID;
    ResourceID sceneTextLoading;
    ResourceID textMessageScreen;
    ResourceID textLoadingScreen;

    bool fadeTextInit;
    int counter;

    Clock mClock;


    // TODO(pedro): remvoe this in the future
    Clock mFakeLoadingTime;
    bool isChangeState;
};

}

#endif // LOADINGSCREEN_H
