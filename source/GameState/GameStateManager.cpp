#include "GameStateManager.h"

using namespace ME;

GameStateManager::GameStateManager() {
    mThread = nullptr;
}

void GameStateManager::add(const std::string &name, GameState *gameState) {
    mGameStates[name] = gameState;
    LOG << Log::VERBOSE << "[GameStateManager::add] Game State: " + name
        << " added" << std::endl;
}

void GameStateManager::changeGameState(const std::string &name) {
    ProfileBlock();
    setGameState(name);
}

void GameStateManager::setGameState(const std::string &name) {
    ProfileBlock();
    
    if (mThread != nullptr) {
        delete mThread;
    }

    mNextGameState = name;

    mThread = new std::thread([this]() {
        ProfileBlockStr("thread [GameStateManager::setGameState]");

        // Since we use callback on effects we can change the game state on
        // a black screen from a fade or effect transition
        if (mGameStates.find(mNextGameState) != mGameStates.end()) {
           // initialize the next game state
            mGameStates[mNextGameState]->init();
            mLock.lock();
            mCurrentGameState = mNextGameState;
            mLock.unlock();

            LOG << Log::VERBOSE << "[GameStateManager::setGameState] Set Game State: " + mNextGameState
                << std::endl;

        } else {
            LOG << Log::WARNING
                << "[GameStateManager::setGameState] Game State not found: " + mNextGameState
                << std::endl;
        }
    });

    mThread->detach();
}

GameStateManager::~GameStateManager() {
    delete mThread;

    for(auto& it : mGameStates) {
        delete it.second;
    }
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
        mLock.lock();
        mGameStates[mCurrentGameState]->onEnable(window);
        mLock.unlock();
    } else if (mGameStates[mCurrentGameState]->getCurrentStatus()
               == GameState::Status::ON_DISABLE) {
        // on disable
        mLock.lock();
        mGameStates[mCurrentGameState]->onDisable(window);
        mLock.unlock();
    } else if (mGameStates[mCurrentGameState]->getCurrentStatus()
               == GameState::Status::ON_PLAYING) {
        // or on playing
        mLock.lock();
        mGameStates[mCurrentGameState]->onPlaying(window);
        mLock.unlock();
    }
}

void GameStateManager::update() {
    if (mGameStates[mCurrentGameState]->isPlaying()) {
        mLock.lock();
        mGameStates[mCurrentGameState]->update();
        mLock.unlock();
    }
}

void GameStateManager::handleEvents(Event &evt) {
    mLock.lock();
    mGameStates[mCurrentGameState]->handleEvents(evt);
    mLock.unlock();
}
