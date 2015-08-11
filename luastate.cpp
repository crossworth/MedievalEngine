#include "luastate.h"
#include "gameengine.h"
#include "fade.h"

using namespace ME;

luaState::luaState(std::string name, std::string path) {
    this->name = name;
    this->path = path;
}

void luaState::init() {
    gameState::setState(INIT);
    mLua->doFile(path + "/scripts/init.lua");
    running = true;
}

void luaState::render() {
    renderWindow* mWindow = renderWindow::getInstance();
    mWindow->getRenderWindow()->setTitle(ENGINE_DEFAULTS::ENGINE_NAME + " - State: " + gameState::getStateString());

    for(unsigned int i = 0; i < mEffects.size(); i++) {
        mEffects.at(i)->draw();
    }

    switch (gameState::getState()) {
    case RENDER:
        mLua->doFile(path + "/scripts/render.lua");
        break;
    case PLAY:
        mLua->doFile(path + "/scripts/play.lua");
        break;
    case PAUSE:
        mLua->doFile(path + "/scripts/pause.lua");
        break;
    case ENABLE_TRANSITION:
        mLua->doFile(path + "/scripts/enable_transition.lua");
        break;
    case DISABLE_TRANSITION:
        mLua->doFile(path + "/scripts/disable_transition.lua");
        break;
    default:
        break;
    }


}


void luaState::handleEvents() {
    while(mRender->pollEvent(mEvent)) {
        if (mEvent.type == sf::Event::Closed || ( mEvent.type == sf::Event::KeyPressed && mEvent.key.code == sf::Keyboard::Escape )) {
            mLua->doFile(path + "/scripts/events/close.lua");
            mRender->close();
        }
        if (mEvent.type == sf::Event::GainedFocus) {
            mLua->doFile(path + "/scripts/events/gained_focus.lua");
            mRender->hasFocus = true;
        }
        if (mEvent.type == sf::Event::LostFocus) {
            mRender->hasFocus = false;
            mLua->doFile(path + "/scripts/events/lost_focus.lua");
        }
        if (mEvent.type == sf::Event::KeyReleased) {
            mLua->doFile(path + "/scripts/events/key_released.lua");
        }
        if (mEvent.type == sf::Event::KeyPressed) {
            mLua->doFile(path + "/scripts/events/key_pressed.lua");
        }
        if (mEvent.type == sf::Event::MouseButtonPressed ){
            mLua->doFile(path + "/scripts/events/mouse_button_pressed.lua");
        }
        if (mEvent.type == sf::Event::MouseButtonReleased) {
            mLua->doFile(path + "/scripts/events/mouse_button_released.lua");
        }
        if (mEvent.type == sf::Event::MouseWheelMoved) {
            mLua->doFile(path + "/scripts/events/mouse_wheel_moved.lua");
        }
    }
}

luaState::~luaState() {

}

void luaState::update() {
    if (running) {
        mLua->doFile(path + "/scripts/update.lua");


        for(auto it = mEffects.begin(); it != mEffects.end(); it++) {
            if ((*it)->done()) {
                mLua->callFunction("effectDone", (*it)->getSpriteName(), (*it)->getEffectName());
                delete *it;
                std::cout << mEffects.size() << std::endl;
            } else {
                (*it)->update();
            }
        }



    }
}

void luaState::onEnableTransition() {
    gameState::setState(ENABLE_TRANSITION);
}

void luaState::onDisableTransition() {
    gameState::setState(DISABLE_TRANSITION);
}

void luaState::restart() {
    this->init();
}

void luaState::play() {
    gameState::setState(PLAY);
    running = true;
}

void luaState::pause() {
    gameState::setState(PAUSE);
    running = false;
}
