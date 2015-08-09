#include "luastate.h"
#include "gameengine.h"

using namespace ME;

luaState::luaState(std::string name, std::string path) {
    this->name = name;
    this->path = path;
}

void luaState::init() {
    mLua->doFile(path + "/scripts/init.lua");
}

void luaState::render() {
   mLua->doFile(path + "/scripts/render.lua");
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
    mLua->doFile(path + "/scripts/update.lua");
}

void luaState::onEnableTransition() {
    mLua->doFile(path + "/scripts/enable_transition.lua");
}

void luaState::onDisableTransition() {
    mLua->doFile(path + "/scripts/disable_transition.lua");
}

void luaState::restart() {
    this->init();
}

void luaState::play() {
    running = true;
}

void luaState::pause() {
    running = false;
}
