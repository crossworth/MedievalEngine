#include "GameStateManager.h"

using namespace ME;

GameStateManager::GameStateManager() {

}

void GameStateManager::add(const std::string &name, GameState *gameState) {
    mGameStates[name] = gameState;
}

void GameStateManager::changeGameState(const std::string &name) {

}

void GameStateManager::setGameState(const std::string &name) {
    mCurrentGameState = name;
}

void GameStateManager::remove(const std::string &name) {

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

void GameStateManager::handleEvents(sf::Event &evt) {
    mGameStates[mCurrentGameState]->handleEvents(evt);
}

