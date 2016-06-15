#ifndef MEDIEVALENGINE_GAMESTATE_LOADINGSCREEN_H_
#define MEDIEVALENGINE_GAMESTATE_LOADINGSCREEN_H_

#include "GameState/GameState.h"

namespace ME {

class LoadingScreen : public GameState {
public:
    LoadingScreen();
    ~LoadingScreen();

    void update(const uint64 &delta);
    void handleEvents(Event &evt);
    void draw(Window &window);
    void pause();
    void resume();
private:

};

}

#endif // MEDIEVALENGINE_GAMESTATE_LOADINGSCREEN_H_
