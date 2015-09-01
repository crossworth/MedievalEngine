#include "GameState.h"
#include "Engine/MedievalEngine.h"

using namespace ME;

GameState::GameState() {
    mIsDone        = false;
    mIsPlaying     = true;
    mCurrentStatus = GAME_STATUS::ON_ENABLE;
    mEngine        = nullptr;
}

void GameState::registerEngine(MedievalEngine* engine) {
    mEngine    = engine;
    mResources = engine->getResourceManager();
}

void GameState::play() {
    mIsPlaying = true;
}

void GameState::pause() {
    mIsPlaying = false;
}

bool GameState::isPlaying() {
    return mIsPlaying;
}

void GameState::restart() {
    mIsDone        = false;
    mIsPlaying     = true;
    mCurrentStatus = GAME_STATUS::ON_ENABLE;
}

GameState::GAME_STATUS GameState::getCurrentStatus() {
    return mCurrentStatus;
}

void GameState::setCurrentStatus(const GameState::GAME_STATUS &status) {
    mCurrentStatus = status;
}

