#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H
#include "GameState/GameState.h"

namespace ME {

class LoadingScreen : public GameState {
public:
    LoadingScreen();
    void init();
    void create();
    void onEnable(Window& window);
    void onDisable(Window& window);
    void onPlaying(Window& window);
    void update();
    void handleEvents(Event& evt);
private:
    Sprite* sceneBGPtr;
    Text* textMessageScreen;
    Text* textLoadingScreen;

    bool fadeTextInit;
    int counter;

    Clock mClock;

    Clock mMinWaitTime;
    bool mIsStateChanging;
    static ResourceID menuMusic;
};

}

#endif // LOADINGSCREEN_H
