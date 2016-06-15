#ifndef MEDIEVALENGINE_GAMESTATE_GAMESTATEMANAGER_H_
#define MEDIEVALENGINE_GAMESTATE_GAMESTATEMANAGER_H_

#include <deque>

#include "GameState/LoadingScreen.h"
// #include "GameState/MenuScreen.h"
// #include "GameState/OptionsScreen.h"


namespace  ME {

class GameStateManager {
public:
    GameStateManager();

    void push(GameState *gameState);
    void pop();
    GameState* getCurrentGameState();

    void draw(Window &window);
    void update(const uint64 &delta);
    void handleEvents(Event &evt);

    inline void pauseCurrent() {
        this->getCurrentGameState()->pause();
    }

    inline void resumeCurrent() {
        this->getCurrentGameState()->resume();
    }

    ~GameStateManager();
private:
    std::deque<GameState*> mGameStates;
};
}

#endif // MEDIEVALENGINE_GAMESTATE_GAMESTATEMANAGER_H_
