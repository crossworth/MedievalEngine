#include "GameState.h"
#include "Engine/MedievalEngine.h"

using namespace ME;

GameState::GameState() {
    mIsDone        = false;
    mIsPlaying     = true;
    mCurrentStatus = GameState::Status::ON_ENABLE;
    mEngine        = nullptr;
}

void GameState::registerEngine(MedievalEngine* engine) {
    mEngine    = engine;
    mResources = engine->getResourceManager();
    mGUI.registerEngine(mEngine);
    create();
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
    mCurrentStatus = GameState::Status::ON_ENABLE;
}

GameState::Status GameState::getCurrentStatus() {
    return mCurrentStatus;
}

void GameState::setCurrentStatus(const GameState::Status &status) {
    mCurrentStatus = status;
}
