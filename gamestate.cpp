#include "gamestate.h"

using namespace ME;

gameState::gameState() : running(false) {
    assets  = AssetsManager::getInstance();
    mRender = renderWindow::getInstance();
    mLua    = LuaEngine::getInstace();
}

bool gameState::isRunning() {
    return running;
}


gameState::~gameState() {

}

void gameState::registerGameEngine(gameEngine *gm) {
    mGameEngine = gm;
}
