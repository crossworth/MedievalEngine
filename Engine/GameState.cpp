#include "GameState.h"
#include "MedievalEngine.h"

using namespace ME;

GameState::GameState() {
    mIsDone        = false;
    mIsPlaying     = true;
    mCurrentStatus = GAMESTATE_STATUS::ON_ENABLE;
    mEngine        = nullptr;
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
    mCurrentStatus = GAMESTATE_STATUS::ON_ENABLE;
}

GAMESTATE_STATUS GameState::getCurrentStatus() {
    return mCurrentStatus;
}

void GameState::setCurrentStatus(const GAMESTATE_STATUS &status) {
    mCurrentStatus = status;
}

