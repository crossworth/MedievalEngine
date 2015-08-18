#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H
#include <Engine/GameState.h>

namespace ME {

class LoadingScreen : public GameState {
public:
    LoadingScreen(MedievalEngine* engine);
    void init();
    void onEnable(Window &window);
    void onDisable(Window &window);
    void onPlaying(Window &window);
    void update();
    void handleEvents(Event &evt);
};

}

#endif // LOADINGSCREEN_H
