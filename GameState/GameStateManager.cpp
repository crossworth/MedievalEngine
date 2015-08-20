#include "GameStateManager.h"

using namespace ME;

GameStateManager::GameStateManager() {

}

void GameStateManager::add(const std::string &name, GameState *gameState) {
    mGameStates[name] = gameState;
    LOG << Log::VERBOSE << "[GameStateManager::add] Game State: " << name.c_str() << " added" << std::endl;
}

void GameStateManager::changeGameState(const std::string &name) {
    LOG << Log::VERBOSE << "[GameStateManager::changeGameState] Change Game State: " << name.c_str() << std::endl;

}

void GameStateManager::setGameState(const std::string &name) {
    LOG << Log::VERBOSE << "[GameStateManager::setGameState] Set Game State: " << name.c_str() << std::endl;
    mCurrentGameState = name;
    mGameStates[mCurrentGameState]->init();
}

void GameStateManager::remove(const std::string &name) {
    LOG << Log::VERBOSE << "[GameStateManager::remove] Remove Game State: " << name.c_str() << std::endl;
}

std::string GameStateManager::getCurrentGameState() {
    return mCurrentGameState;
}

void GameStateManager::draw(Window &window) {
    if (mGameStates[mCurrentGameState]->getCurrentStatus() == GAMESTATE_STATUS::ON_ENABLE) {
        mGameStates[mCurrentGameState]->onEnable(window);
    } else if (mGameStates[mCurrentGameState]->getCurrentStatus() == GAMESTATE_STATUS::ON_DISABLE) {
        mGameStates[mCurrentGameState]->onDisable(window);
    } else {
        mGameStates[mCurrentGameState]->onPlaying(window);
    }
}

void GameStateManager::update() {
    if (mGameStates[mCurrentGameState]->isPlaying()) {
        mGameStates[mCurrentGameState]->update();
    }
}

void GameStateManager::handleEvents(Event &evt) {
    mGameStates[mCurrentGameState]->handleEvents(evt);
}

