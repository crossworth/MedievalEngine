#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H
#include <thread>
#include "GameState/LoadingScreen.h"
#include "GameState/MenuScreen.h"
#include "GameState/OptionsScreen.h"


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

    ~GameStateManager();
private:
    std::mutex mLock;
    std::thread* mThread;
    std::string mNextGameState;
    std::string mCurrentGameState;
    std::unordered_map<std::string, GameState*> mGameStates;
};

}

#endif // GAMESTATEMANAGER_H
