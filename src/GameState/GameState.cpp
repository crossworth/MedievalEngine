#include "GameState.h"
#include "Engine/MedievalEngine.h"


using namespace ME;

GameState::GameState() {
    mPlaying       = true;
    mStatus        = GameState::Status::PLAYING;
    mUpdateOnPause = false;
}

GameState::~GameState() {
    
}