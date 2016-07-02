#include "GameStateManager.h"

using namespace ME;

GameStateManager::GameStateManager() {
    LuaAPI::state.set_function("pause_game_state", &GameStateManager::pauseCurrent);
    LuaExportAPI::exports("pause_game_state", "void", "void", LuaExportType::FUNCTION, "Pause the current game state");

    LuaAPI::state.set_function("resume_game_state", &GameStateManager::resumeCurrent);
    LuaExportAPI::exports("pause_game_state", "void", "void", LuaExportType::FUNCTION, "Resume the current game state");
}

GameStateManager::~GameStateManager() {

}

void GameStateManager::push(GameState *gameState) {
    mGameStates.push_front(gameState);
}

void GameStateManager::pop() {
    mGameStates.pop_front();
}

GameState* GameStateManager::getCurrentGameState() {
    if (mGameStates.size() > 0) {
        return mGameStates.front();
    } else {
        return nullptr;
    }
}

void GameStateManager::draw(Window &window) {
    if (getCurrentGameState() == nullptr) {
        return;
    }

    getCurrentGameState()->draw(window);
}

void GameStateManager::update(const uint64 &delta) {
    if (getCurrentGameState() == nullptr) {
        return;
    }

    std::deque<GameState*>::iterator it = mGameStates.begin();

    for(; it != mGameStates.end(); it++) {
        if ((*it)->updateOnPause()) {
            (*it)->update(delta);
        }
    }
}

void GameStateManager::handleEvents(Event &evt) {
    if (getCurrentGameState() == nullptr) {
        return;
    }
    
    getCurrentGameState()->handleEvents(evt);
}
