#include "GameStateManager.h"

using namespace ME;

GameStateManager::GameStateManager() {

}

void GameStateManager::add(const std::string &name, GameState *gameState) {
    mGameStates[name] = gameState;
    LOG << Log::VERBOSE << "[GameStateManager::add] Game State: " + name
        << " added" << std::endl;
}

void GameStateManager::changeGameState(const std::string &name) {
    ProfileBlock();

    LOG << Log::VERBOSE
        << "[GameStateManager::changeGameState] Change Game State: " + name 
        << std::endl;

    // Since we use callback on effects we can change the game state on
    // a black screen from a fade or effect transition
    if (mGameStates.find(name) != mGameStates.end()) {
        setGameState(name);
    } else {
        LOG << Log::WARNING
            << "[GameStateManager::changeGameState] Game State not found: " + name
            << std::endl;
    }
}

void GameStateManager::setGameState(const std::string &name) {
    ProfileBlock();
    
    LOG << Log::VERBOSE << "[GameStateManager::setGameState] Set Game State: " + name
        << std::endl;

    mCurrentGameState = name;
    // initialize the next game state
    mGameStates[mCurrentGameState]->init();
}

void GameStateManager::remove(const std::string &name) {
    LOG << Log::VERBOSE << "[GameStateManager::remove] Remove Game State: " + name
        << std::endl;
}

std::string GameStateManager::getCurrentGameState() {
    return mCurrentGameState;
}

GameState* GameStateManager::getGameState(const std::string& name) {
    if (mGameStates.find(name) != mGameStates.end()) {
        return mGameStates[name];
    } else {
        LOG << Log::WARNING << "[GameStateManager::getGameState] Game State not found: " + name
            << std::endl;
        return nullptr;
    }
}

void GameStateManager::draw(Window &window) {
    // Call the appropriate game state draw function
    // based on the current game status
    if (mGameStates[mCurrentGameState]->getCurrentStatus()
        == GameState::Status::ON_ENABLE) {
        // on enable
        mGameStates[mCurrentGameState]->onEnable(window);
    } else if (mGameStates[mCurrentGameState]->getCurrentStatus()
               == GameState::Status::ON_DISABLE) {
        // on disable
        mGameStates[mCurrentGameState]->onDisable(window);
    } else if (mGameStates[mCurrentGameState]->getCurrentStatus()
               == GameState::Status::ON_PLAYING) {
        // or on playing
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
