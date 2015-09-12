#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H
#include "GameState/LoadingScreen.h"
#include "GameState/MenuScreen.h"
#include "GameState/OptionsScreen.h"
#include "Helper/Profiler.h"


namespace  ME {

class GameStateManager {
public:
    GameStateManager();
    void add(const std::string& name, GameState* gameState);
    void changeGameState(const std::string& name);
    void setGameState(const std::string& name);
    void remove(const std::string& name);
    std::string getCurrentGameState();
    GameState* getGameState(const std::string& name);

    void draw(Window& window);
    void update();
    void handleEvents(Event& evt);
private:
    std::string mCurrentGameState;
    std::map<std::string, GameState*> mGameStates;
};

}

#endif // GAMESTATEMANAGER_H
