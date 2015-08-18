#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H
#include <Engine/GameState.h>
#include <Helper/ID.h>

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

private:
    MEid idBackground;
    MEid idLogo;
};

}

#endif // LOADINGSCREEN_H