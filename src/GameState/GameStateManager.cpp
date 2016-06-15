#include "GameStateManager.h"

using namespace ME;

GameStateManager::GameStateManager() {

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
    return mGameStates.front();
}

void GameStateManager::draw(Window &window) {
    getCurrentGameState()->draw(window);
}

void GameStateManager::update(const uint64 &delta) {
    std::deque<GameState*>::iterator it = mGameStates.begin();

    for(; it != mGameStates.end(); it++) {
        if ((*it)->updateOnPause()) {
            (*it)->update(delta);
        }
    }
}

void GameStateManager::handleEvents(Event &evt) {
    getCurrentGameState()->handleEvents(evt);
}
