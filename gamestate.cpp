#include "gamestate.h"

using namespace ME;

gameState::gameState() : running(false) {
    mState  = INIT;
    assets  = AssetsManager::getInstance();
    mRender = renderWindow::getInstance();
    mLua    = LuaEngine::getInstace();
}

bool gameState::isRunning() {
    return running;
}

GAME_STATE gameState::getState() {
    return mState;
}

std::string gameState::getStateString() {
    switch (mState) {
    case INIT:
        return "init";
        break;
    case PLAY:
        return "play";
        break;
    case PAUSE:
        return "pause";
        break;
    case ENABLE_TRANSITION:
        return "enable_transition";
        break;
    case DISABLE_TRANSITION:
        return "disable_transition";
        break;
    case RENDER:
        return "render";
        break;
    default:
        return "unkonw";
        break;
    }
}

void gameState::setState(const GAME_STATE &state) {
    mState = state;
}

void gameState::addEffect(Effects *effect) {
    mEffects.push_back(effect);
}

void gameState::addCallBack(CallBack *callBack) {
    mCallBacks.push_back(callBack);
}

void gameState::setState(const std::string &state) {
    std::string tmp = state;
    std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);


    if (state == "init") {
        mState = INIT;
    }
    if (state == "play") {
        mState = PLAY;
    }
    if (state == "pause") {
        mState = PAUSE;
    }
    if (state == "enable_transition") {
        mState = ENABLE_TRANSITION;
    }
    if (state == "disable_transition") {
        mState = DISABLE_TRANSITION;
    }
    if (state == "render") {
        mState = RENDER;
    }

    Debugger *dbg = Debugger::getInstance();
    dbg->log(VERBOSE, 1, ("[gameState::setState] " + getStateString()).c_str());
}

gameState::~gameState() {

}

float gameState::getTime() {
    sf::Time seconds = mClock.getElapsedTime();
    return seconds.asSeconds();
}

void gameState::restartTime() {
    mClock.restart();
}

void gameState::registerGameEngine(gameEngine *gm) {
    mGameEngine = gm;
}
